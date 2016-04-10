//  main.c
//  word2vec
//
//  Created by suhui on 15/3/20.
//  Copyright (c) 2015�� suhui. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

// һ��word����󳤶�
#define MAX_STRING 100
// ��f�����������л��棬�洢1000������Ҫ�õ�ʱ����
#define EXP_TABLE_SIZE 1000
// �����㵽6 (exp^6 / (exp^6 + 1))����С���㵽-6 (exp^-6 / (exp^-6 + 1))
#define MAX_EXP 6
// �������ľ��ӳ���
#define MAX_SENTENCE_LENGTH 1000
// ������Ļ��������볤��
#define MAX_CODE_LENGTH 40
// ��ϣ������̽�⣬���Ŷ�ַ����װ��ϵ��0.7
const int vocab_hash_size = 30000000;

//������������
typedef float real;

struct vocab_word {
    long long cn; //���ʴ�Ƶ
    int * point ; //���������дӸ��ڵ㵽�ôʵ�·�������·����ÿ����Ҷ��������
    char * word, *code ,codelen; //  �ֱ��Ǵʵ����棬���������룬���볤��
};


// ѵ���ļ�������ļ����ƶ���
char train_file[MAX_STRING], output_file[MAX_STRING];
// �ʻ������ļ��ʹʻ�������ļ����ƶ���
char save_vocab_file[MAX_STRING], read_vocab_file[MAX_STRING];

// �����ʻ���ṹ��
struct vocab_word *vocab;
// binary 0��vectors.bin���Ϊ�����ƣ�Ĭ�ϣ���1��Ϊ�ı���ʽ
// cbow 1ʹ��cbow��ܣ�0ʹ��skip-gram���
// debug_mode ����0��������Ϻ����������Ϣ������1������ѵ���ʻ��ʱ�������Ϣ��ѵ�������������Ϣ
// window ���ڴ�С����cbow�б�ʾ��word vector������sum��Χ����skip-gram�б�ʾ��max space between words��w1,w2,p(w1 | w2)��
// min_count ɾ����β�ʵĴ�Ƶ��׼
// num_threads �߳���
// min_reduce ReduceVocabɾ����ƵС�����ֵ�Ĵʣ���Ϊ��ϣ���ܹ�����װ��Ĵʻ��������޵�
int binary = 0, cbow = 0, debug_mode = 2, window = 5, min_count = 5, num_threads = 1, min_reduce = 1;
int *vocab_hash; // �ʻ����hash�洢���±��Ǵʵ�hash�������Ǵ���vocab�е�λ�ã�a[word_hash] = word index in vocab
// vocab_max_size �ʻ������󳤶ȣ�����������ÿ����1000
// vocab_size �ʻ�������г��ȣ��ӽ�vocab_max_size��ʱ�������
// layer1_size ����Ľڵ���
long long vocab_max_size = 1000, vocab_size = 0, layer1_size = 100;
// train_words ѵ���ĵ�����������Ƶ�ۼӣ�
// word_count_actual �Ѿ�ѵ�����word����
// file_size ѵ���ļ���С��ftell�õ�
// classes ���word clusters�������
long long train_words = 0, word_count_actual = 0, file_size = 0, classes = 0;
// alpha BP�㷨��ѧϰ���ʣ��������Զ�����
// starting_alpha ��ʼalphaֵ
// sample �ǲ������ʵĲ������ǲ�����Ŀ������һ�����ʾܾ���Ƶ�ʣ�ʹ�õ�Ƶ���и�������ʣ�Ĭ��Ϊ0�����������ǲ���
real alpha = 0.025, starting_alpha, sample = 0;
// syn0 ���ʵ��������� concatenate word vectors
// syn1 hs(hierarchical softmax)�㷨������ڵ㵽��������������Ҷ����ӳ��Ȩ��
// syn1neg ns(negative sampling)������ڵ㵽���������ӳ��Ȩ��
// expTable Ԥ�ȴ洢f����������㷨ִ���в��
real *syn0, *syn1, *syn1neg, *expTable;
// start �㷨���е���ʼʱ�䣬�����ڼ���ƽ��ÿ���Ӵ������ٴ�
clock_t start;

// hs ����hs����ns�ı�־λ��Ĭ�ϲ���hs
int hs = 1, negative = 0;
// table_size ��̬�������Ĺ�ģ
// table ������
const int table_size = 1e8;
int *table;

// ���ݴ�Ƶ���ɲ�����
void InitUnigramTable() {
    int a, i;
    long long train_words_pow = 0;
    real d1, power = 0.75; // �������Ƶ��power�η�������
    table = (int *)malloc(table_size * sizeof(int));
    for (a = 0; a < vocab_size; a++) train_words_pow += pow(vocab[a].cn, power);
    i = 0;
    d1 = pow(vocab[i].cn, power) / (real)train_words_pow; // ��һ���ʳ��ֵĸ���
    for (a = 0; a < table_size; a++) {
        table[a] = i;
        if (a / (real)table_size > d1) {
            i++;
            d1 += pow(vocab[i].cn, power) / (real)train_words_pow;
        }
        if (i >= vocab_size) i = vocab_size - 1; // �������һ�θ��ʣ���ֹԽ��
    }
}


//���ļ�file��ÿ�ζ�ȡһ������
void ReadWord(char * word, FILE * file){

    int a = 0, ch;
    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == 13)  continue; //����һ�� \r
        if ((ch == ' ') || (ch == '\t') || (ch == '\n') ) {
            if(a > 0){
                if (ch == '\n') ungetc(ch, file);// ��һ���ַ����˵���������
                break;
            }
            if (ch == '\n') {
                strcpy(word, (char *)"</s>");
                return;
            }else continue;
        }
        word[a] = ch;
        a++;
        if (a >= MAX_STRING - 1) a--;
    }
    word[a] = 0;
}

int GetWordHash(char * word) {
    unsigned long long a ,hash = 0;
    for (a = 0; a < strlen(word); a++) {
        hash = hash * 257 + word[a];
    }
    hash = hash % vocab_hash_size;
    return hash;
}

int AddWordToVocab(char * word){
    unsigned int hash, lengh = strlen(word) + 1;
    if (lengh > MAX_STRING) lengh = MAX_STRING;
    vocab[vocab_size].word = (char *) calloc(lengh, sizeof(char));
    strcpy(vocab[vocab_size].word, word);
    vocab[vocab_size].cn = 0;
    vocab_size++;
    if (vocab_size + 2 >= vocab_max_size ) {
        vocab_max_size += 1000;// ÿ������1000����λ
        vocab = (struct vocab_word *)realloc(vocab, vocab_max_size * sizeof(struct vocab_word));
    }
    hash = GetWordHash(word);
    while (vocab_hash[hash] != -1)  hash = (hash + 1) % vocab_hash_size; // ����̽��hash
    vocab_hash[hash] = vocab_size - 1;// ��¼�ڴʻ���еĴ洢λ��
    return  vocab_size - 1;// �������ӵĵ����ڴʻ���еĴ洢λ��
}

//// �ȽϺ������ʻ����ʹ�ô�Ƶ��������(qsort)
int  VocabCompare(const *a, const *b){
    return ((struct vocab_word *)b)->cn - ((struct vocab_word *)a)->cn;
}


//���ݵ��ʴ�Ƶ����
void SortVocab() {
    int a, size;
    unsigned int hash;
    // ����
    // ���ұ�֤</s>�ڵ�һλ
    qsort(&vocab[1], vocab_size - 1, sizeof(struct vocab_word), VocabCompare);//�ʻ������
    for (a = 0; a < vocab_hash_size; a++) vocab_hash[a] = -1;//�ʻ������ˣ���ϣ��¼��indexҲ���ˣ����е�hash��¼�����������ؽ�
    size = vocab_size;
    train_words = 0;// ����ѵ���Ĵʻ���������Ƶ�ۼӣ�
    for (a = 0; a < size; a++) {
        // ɾ���ر��Ƶ�Ĵ�
        if (vocab[a].cn < min_count) {
            vocab_size--;
            free(vocab[vocab_size].word);
        } else {
            //ԭ����hashʧЧ��Ҫ���¼���
            hash=GetWordHash(vocab[a].word);
            while (vocab_hash[hash] != -1) hash = (hash + 1) % vocab_hash_size;
            vocab_hash[hash] = a;
            train_words += vocab[a].cn;
        }
    }
    vocab = (struct vocab_word *)realloc(vocab, (vocab_size + 1) * sizeof(struct vocab_word));
    // �������������·���Ĵʻ����������ռ�
    for (a = 0; a < vocab_size; a++) {
        vocab[a].code = (char *)calloc(MAX_CODE_LENGTH, sizeof(char));
        vocab[a].point = (int *)calloc(MAX_CODE_LENGTH, sizeof(int));
    }
}

// ����ʻ���ļ����ʻ�����ݽṹ
void ReadVocab() {
    long long a, i = 0;
    char c;
    char word[MAX_STRING];
    FILE * fin = fopen(read_vocab_file, "rb");
    if (fin == NULL) {
        printf("Vocabulary file not found\n");
        exit(1);
    }
    for (a = 0; a < vocab_hash_size; a++)
        vocab_hash[a] = -1;
    vocab_size = 0;
    while (1) {
        ReadWord(word, fin);
        if (feof(fin)) break;
        fscanf(fin, "%lld%c", &vocab[a].cn, &c);
        i++;
    }
    SortVocab();
    if (debug_mode > 0) {
        printf("Vocab size: %lld\n", vocab_size);
        printf("Words in train file: %lld\n", train_words);
    }
    fin = fopen(train_file, "rb");
    if (fin == NULL) {
        printf("ERROR: training data file not found!\n");
        exit(1);
    }
    fseek(fin, 0, SEEK_END);
    file_size = ftell(fin);
    fclose(fin);
}

// ����̽�������Ŷ�ַ��
int SearchVocab(char * word) {
    unsigned int hash = GetWordHash(word);
    while (1) {
        // û�������
        if (vocab_hash[hash] == -1) return -1;
        if (!strcmp(word, vocab[vocab_hash[hash]].word)) return vocab_hash[hash];
        hash = (hash + 1) % vocab_hash_size;
    }
    return -1; // ����������Զ���в���......
}

void ReduceVocab() {
    // reduces the vocabulary by removing infrequent tokens.
    int a, b = 0;
    unsigned int hash;
    // ���ʣ��b���ʣ���Ƶ������min_reduce
    for (a = 0; a < vocab_size; a++) {
        if (vocab[a].cn > min_reduce) {
            vocab[b].cn = vocab[a].cn;
            vocab[b].word = vocab[a].word;
            b++;
        } else {
            free (vocab[a].word);
        }
    }
    vocab_size = b;
    // ���·���hash����
    for (a = 0; a < vocab_hash_size; a++) vocab_hash[a] = -1;
    for (a = 0; a < vocab_size; a++) {
        hash = GetWordHash(vocab[a].word);
        while (vocab_hash[hash] != -1) hash = (hash + 1) % vocab_hash_size;
        vocab_hash[hash] = a;
    }
    fflush(stdout);
    min_reduce++;
}

// װ��ѵ���ļ����ʻ�����ݽṹ
void LearnVocabFromTrainFile() {
    char word[MAX_STRING];
    FILE * fin;
    long long a, i;
    for (a = 0; a < vocab_hash_size; a++) vocab_hash[a] = -1;
    fin = fopen(train_file, "rb");
    if (fin == NULL) {
        printf("ERROR: training data file not found!\n");
        exit(1);
    }
    vocab_size = 0;
    // �������ӵ��ǻس�
    AddWordToVocab((char *)"</s>");
    while (1) {
        ReadWord(word, fin);
        if (feof(fin)) break;
        train_words++;
        if ((debug_mode > 1) && (train_words % 100000 == 0)) {
            printf("%lldK%c", train_words / 1000, 13);
            fflush(stdout);
        }
        i = SearchVocab(word);
        if (i == -1) {// ���������ʲ����ڣ����ǽ������hash��
            a = AddWordToVocab(word);
            vocab[a].cn = 1;
        } else vocab[i].cn++;// �����Ƶ��һ
        // �������װ��ϵ�������ʻ������
        if (vocab_size > vocab_hash_size * 0.7) ReduceVocab();
    }
    SortVocab();
    if (debug_mode > 0) {
        printf("Vocab size: %lld\n", vocab_size);
        printf("Words in train file: %lld\n", train_words);
    }
    file_size = ftell(fin);//�ļ���С
    fclose(fin);
}

// ������ʺʹ�Ƶ���ļ�
void SaveVocab() {
    long long i;
    FILE * fo = fopen(save_vocab_file, "wb");
    for (i = 0; i < vocab_size; i++) {
        fprintf(fo, "%s %lld\n", vocab[i].word, vocab[i].cn);
    }
    fclose(fo);
}

// ���ݴ�Ƶ���ɻ�������
void CreateBinaryTree() {
    long long a, b, i;
    long long min1i, min2i;
    long long pos1, pos2;
    long long point[MAX_CODE_LENGTH];// ��ı���ֵ
    char code[MAX_CODE_LENGTH];
    long long *count = (long long *)calloc(vocab_size * 2 + 1, sizeof(long long));
    long long *binary = (long long *)calloc(vocab_size * 2 + 1, sizeof(long long));
    long long *parent_node = (long long *)calloc(vocab_size * 2 + 1, sizeof(long long));
    for (a = 0; a < vocab_size; a++) count[a] = vocab[a].cn;
    for (a = vocab_size; a < vocab_size * 2; a++) count[a] = 1e15;
    pos1 = vocab_size - 1;
    pos2 = vocab_size;
    for (a = 0; a < vocab_size - 1; a++) {
        // ÿ��Ѱ��������С�ĵ����ϲ�����С�ĵ�Ϊ0����С�ĵ�Ϊ1
        if (pos1 >= 0) {
            if (count[pos1] < count[pos2]) {
                min1i = pos1;
                pos1--;
            } else {
                min1i = pos2;
                pos2++;
            }
        } else {
            min1i = pos2;
            pos2++;
        }
        if (pos1 >= 0) {
            if (count[pos1] < count[pos2]) {
                min2i = pos1;
                pos1--;
            } else {
                min2i = pos2;
                pos2++;
            }
        } else {
            min2i = pos2;
            pos2++;
        }
        count[vocab_size + a] = count[min1i] + count[min2i];
        parent_node[min1i] = vocab_size + a;
        parent_node[min2i] = vocab_size + a;
        binary[min2i] = 1;
    }
    // ˳�Ÿ��ӹ�ϵ�һر���
    for (a = 0; a < vocab_size; a++) {
        b = a;
        i = 0;
        while (1) {
            code[i] = binary[b];
            point[i] = b;

            i++;
            b = parent_node[b];
            if (b == vocab_size * 2 - 2) break;
        }
        vocab[a].codelen = i;
        vocab[a].point[0] = vocab_size - 2; // ���򣬰ѵ�һ����ֵΪroot����2*vocab_size - 2 - vocab_size��
        for (b = 0; b < i; b++) {
            vocab[a].code[i - b - 1] = code[b];// ��������û�и��ڵ㣬������0��������1
            vocab[a].point[i - b] = point[b] - vocab_size;
        }
    }
    free(count);
    free(binary);
    free(parent_node);
}


int ReadWordIndex(FILE * fin) {
    char word[MAX_STRING];
    ReadWord(word, fin);
    if (feof(fin)) return -1;
    return SearchVocab(word);
}

// ����ṹ��ʼ��
void InitNet() {
    // intialize the neural network structure
    long long a, b;
    // posix_memalign() �ɹ�ʱ�᷵��size�ֽڵĶ�̬�ڴ棬��������ڴ�ĵ�ַ��alignment(������128)�ı���
    // syn0 �洢����word vectors
    a = posix_memlign((void **)&syn0, 128, (long long)vocab_size * layer1_size * sizeof(real));
    if (syn0 == NULL) {
        printf("Memory allocation failed\n"); exit(1);
    }
    // Hierarchical Softmax
    if (hs) {
        // hs�У���syn1
        a = posix_memlign((void **)&syn1, 128, (long long)vocab_size * layer1_size * sizeof(real));
        if (syn1 == NULL) {printf("Memory allocation failed\n"); exit(1);}
        for (b = 0; b < layer1_size; b++) for (a = 0; a < vocab_size; a++)
            syn1[a * layer1_size + b] = 0;
    }
    // Negative Sampling
    if (negative > 0) {
        // ns�У���syn1neg
        a = posix_memlign((void **)&syn1neg, 128, (long long)vocab_size * layer1_size * sizeof(real));
        if (syn1neg == NULL) {printf("Memory allocaiton failed\n"); exit(1);}
        for (b = 0; b < layer1_size; b++) for (a = 0; a < vocab_size; a++)
            syn1neg[a * layer1_size + b] = 0;
    }
    for (b = 0; b < layer1_size; b++) for (a = 0; a < vocab_size; a++)
        syn0[a * layer1_size + b] = (rand() / (real)RAND_MAX - 0.5) / layer1_size;//�����ʼ��word vectors
    CreateBinaryTree();// ������������
}

// learning: hs (hierarchical softmax) v.s. negative sampling
// model: cbow v.s. skip gram
void *TrainModelThread(void *id) {
    // word ��sen�����ӵ����ã�������ɺ��ʾ�����еĵ�ǰ����
    // last_word ��һ�����ʣ�����ɨ�贰��
    // sentence_length ��ǰ���ӵĳ��ȣ���������
    // sentence_position ��ǰ�����ڵ�ǰ�����е�index
    long long a, b, d, word, last_word, sentence_length = 0, sentence_position = 0;
    // word_count ��ѵ�������ܳ���
    // last_word_count ����ֵ���Ա�����ѵ�����ϳ��ȳ���ĳ��ֵʱ�����Ϣ
    // sen �������飬��ʾ����
    long long word_count = 0, last_word_count = 0, sen[MAX_SENTENCE_LENGTH + 1];
    // l1 ns�б�ʾword��concatenated word vectors�е���ʼλ�ã�֮��layer1_size�Ƕ�Ӧ��word vector��
    //��Ϊ�Ѿ������ɳ�������
    // l2 cbow��ns��Ȩ����������ʼλ�ã�֮��layer1_size�Ƕ�Ӧ��syn1��syn1neg����Ϊ�Ѿ������ɳ�������
    // c ѭ���еļ�������
    // target ns�е�ǰ��sample
    // label ns�е�ǰsample��label

    long long l1, l2, c, target, label;
    // id �̴߳�����ʱ���룬�������������
    unsigned long long next_random = (long long) id;
    // f e^x / (1/e^x)��fs��ָ��ǰ����Ϊ��0�����׵����ӽڵ�Ϊ0����Ϊ1���ĸ��ʣ�
    // ns��ָlabel��1�ĸ���
    // g ���(f����ʵֵ��ƫ��)��ѧϰ���ʵĳ˻�
    real f, g; // function and gradient
    clock_t now;
    // ����ڵ�
    real * neu1 = (real *)calloc(layer1_size, sizeof(real));
    // ����ۼ����ʵ��Ӧ����Gneu1
    real * neu1e = (real *)calloc(layer1_size, sizeof(real));
    // ���ļ����ݷ���������߳�
    FILE * fi = fopen(train_file, "rb");
    fseek(fi, file_size / (long long)num_threads * (long long)id, SEEK_SET);

    while (1) {
        if (word_count - last_word_count > 10000) {
            word_count_actual += word_count - last_word_count;
            last_word_count = word_count;
            if (debug_mode > 1) {
                now = clock();
                printf("%cAlpah: %f Progress: %.2f%% Words/thread/sec: %.2fk ", 13, alpha,
                       word_count_actual / (real)(train_words + 1) * 100,
                       word_count_actual / ((real)(now - start + 1) / (real)CLOCKS_PER_SEC * 1000));
                fflush(stdout);
            }
            alpha = starting_alpha * (1 - word_count_actual / (real)(train_words + 1)); // �Զ�����ѧϰ����
            if (alpha < starting_alpha * 0.0001) alpha = starting_alpha * 0.0001;// ѧϰ����������
        }
        if (sentence_length == 0) {// �����ǰ���ӳ���Ϊ0
            while(1) {
                word = ReadWordIndex(fi);
                if (feof(fi)) break;// �����ļ�ĩβ
                if (word == -1) continue;// û���������
                word_count++;// ���ʼ�������
                if (word == 0) break;// �Ǹ��س�
                // ������ǲ�����ָ Sub-Sampling��Mikolov ������ָ�������ǲ����ܹ����� 2 �� 10 �����������������ܹ�������Ƶ�ʵı�ʾ���ȡ�
                // ��Ƶ�ʱ��������ʵͣ���Ƶ�ʱ��������ʸ�
                if (sample > 0) {
                    real ran = (sqrt(vocab[word].cn / (sample * train_words)) + 1) * (sample * train_words) / vocab[word].cn;
                    next_random = next_random * (unsigned long long)25214903917 + 11;
                    if (ran < (next_random & 0xFFFF) / (real)65536) continue;
                }
                sen[sentence_length] = word;
                sentence_length++;
                if (sentence_length >= MAX_SENTENCE_LENGTH) break;
            }
            sentence_position = 0;// ��ǰ�����ڵ�ǰ���е�index����ʼֵΪ0
        }
        // ��Ӧwhile�е�break���������ĩβ���˳�
        if (feof(fi)) break;
        // �Ѿ�������һ��threadӦ���Ĺ����������˳�
        if (word_count > train_words / num_threads) break;
        // ȡ�����еĵ�һ�����ʣ���ʼ����BP�㷨
        word = sen[sentence_position];
        if (word == -1) continue;
        // ����ڵ�ֵ������ڵ�����ۼ�������
        for (c = 0; c < layer1_size; c++) neu1[c] = 0;
        for (c = 0; c < layer1_size; c++) neu1e[c] = 0;
        next_random = next_random * (unsigned long long)25214903917 + 11;
        // b�Ǹ��������0��window-1��ָ���˱����㷨����ʵ�ʵĴ��ڴ�С
        b = next_random % window;

        if (cbow) { // train the cbow architecture - HS or NS
            // IN -> HIDDEN
            // �������ڵ�word vectors�ۼӵ�����ڵ���
            for (a = b; a < window * 2 + 1 - b; a++) if (a != window) {
                c = sentence_position - window + a;
                if (c < 0) continue;
                if (c >= sentence_length) continue;
                last_word = sen[c];
                if (last_word == -1) continue;// �������û��
                for (c = 0; c < layer1_size; c++)
                    neu1[c] += syn0[c + last_word * layer1_size];
            }
            // HIERARCHICAL SOFTMAX
            //��ǰ���Ĵ��ڹ��������дӸ��ڵ㵽�ýڵ��·���ϵ�ÿһ�����neu1�����sigmoid������
            //labelΪ1-code[j]
            if (hs) for (d = 0; d < vocab[word].codelen; d++) {
                // �����codelen��ʵ����һ���ģ����Բ��ᴥ��point�������һ������
                f = 0;
                l2 = vocab[word].point[d] * layer1_size;
                // propagate hidden -> output
                // ׼������f
                for (c = 0; c < layer1_size; c++) f += neu1[c] * syn1[c + l2];
                // ����expTable�ڵ����������Ƚϱ���
                if (f <= -MAX_EXP) continue;
                else if (f >= MAX_EXP) continue;
                // ��expTable�в��ң����ټ���
                else f = expTable[(int)((f + MAX_EXP) * (EXP_TABLE_SIZE / MAX_EXP / 2))];
                // g is the gradient multiplied by the learning rate
                g = (1 - vocab[word].code[d] -f) * alpha;
                // propogate errors output -> hidden
                 // ��¼�ۻ������
                for (c = 0; c < layer1_size; c++) neu1e[c] += g * syn1[c + l2];
                // learning weights hidden -> output
                // �������㵽����������Ҷ�ڵ��Ȩ��
                for (c = 0; c < layer1_size; c++) syn1[c + l2] += g * neu1[c];
            }
            // NEGATIVE SAMPLING
            if (negative > 0) for (d = 0; d < negative + 1; d++) {
                if (d == 0) { // ��ǰ�ʵķ�����Ӧ�����1
                    target = word;
                    label = 1;
                } else { // ����ʹ����target��ͬ����Ȼcontinue��labelΪ0��Ҳ��������negative��negative sample
                    next_random = next_random * (unsigned long long)25214903917 + 11;
                    target = table[(next_random >> 16) % table_size];
                    if (target == 0) target = next_random % (vocab_size - 1) + 1;
                    if (target == word) continue;
                    label = 0;
                }
                l2 = target * layer1_size;
                f = 0;
                for (c = 0; c < layer1_size; c++) f += neu1[c] * syn1neg[c + l2];
                // ����ֱ����0��1��û�п��Ǽ��㾫�����⡭��
                if (f > MAX_EXP) g = (label - 1) * alpha;
                else if (f < -MAX_EXP) g = (label - 0) * alpha;
                else g = (label - expTable[(int)((f + MAX_EXP) * (EXP_TABLE_SIZE / MAX_EXP / 2))]) * alpha;
                for (c = 0; c < layer1_size; c++) neu1e[c] += g * syn1neg[c + l2];
                for (c = 0; c < layer1_size; c++) syn1neg[c + l2] += g * neu1[c];
            }
            // hidden -> in
            // ��������ڵ��ۻ���������word vectors
            for (a = b; a < window * 2 + 1 - b; a++) if (a != window) {
                c = sentence_position - window + a;
                if (c < 0) continue;
                if (c >= sentence_length) continue;
                last_word = sen[c];
                if (last_word == -1) continue;
                for (c = 0; c < layer1_size; c++) syn0[c + last_word * layer1_size] += neu1e[c];
            }
        } else {  //train skip-gram
            for (a = b; a < window * 2 + 1 - b; a++) if (a != window) { // Ԥ������ĵĵ��ʣ������ڵĵ��ʣ�
                c = sentence_position - window + a;
                if (c < 0) continue;
                if (c >= sentence_length) continue;
                last_word = sen[c];
                if (last_word == -1) continue;
                l1 = last_word * layer1_size;
                // �ۼ����������
                for (c = 0; c < layer1_size; c++) neu1e[c] = 0;

                // HIERARCHICAL SOFTMAX
                if (hs) for (d = 0; d < vocab[word].codelen; d++) {
                    f = 0;
                    l2 = vocab[word].point[d] * layer1_size;
                    // Propagate hidden -> output
                    // ��Ԥ�ⵥ�ʵ� word vecotr �� ����-����������Ҷ�ڵ�Ȩ�� ���ڻ�
                    for (c = 0; c < layer1_size; c++) f += syn0[c + l1] * syn1[c + l2];
                    // ͬcbow��hs������
                    // if (f <= -MAX_EXP) continue;
                    // else if (f >= MAX_EXP) continue;
                    if (f <= -MAX_EXP) f = 0;
                    else if (f >= MAX_EXP) f = 1;
                    // ��������֮ͬǰ��cbow
                    else f = expTable[(int)((f + MAX_EXP) * (EXP_TABLE_SIZE / MAX_EXP / 2))];
                    // 'g' is the gradient multiplied by the learning rate
                    g = (1 - vocab[word].code[d] - f) * alpha; // �����code[d]��ʵ����һ��ģ�code��λ�ˣ�point��code�Ǵ�λ�ģ�
                    // Propagate errors output -> hidden
                    for (c = 0; c < layer1_size; c++) neu1e[c] += g * syn1[c + l2];
                    // Learn weights hidden -> output
                    for (c = 0; c < layer1_size; c++) syn1[c + l2] += g * syn0[c + l1];
                }
                // NEGATIVE SAMPLING
                if (negative > 0) for (d = 0; d < negative + 1; d++) {
                    if (d == 0) {
                        target = word;
                        label = 1;
                    } else {
                        next_random = next_random * (unsigned long long)25214903917 + 11;
                        target = table[(next_random >> 16) % table_size];
                        if (target == 0) target = next_random % (vocab_size - 1) + 1;
                        if (target == word) continue;
                        label = 0;
                    }
                    l2 = target * layer1_size;
                    f = 0;
                    for (c = 0; c < layer1_size; c++) f += syn0[c + l1] * syn1neg[c + l2];
                    // ��������֮ͬǰ��cbow
                    if (f > MAX_EXP) g = (label - 1) * alpha;
                    else if (f < -MAX_EXP) g = (label - 0) * alpha;
                    else g = (label - expTable[(int)((f + MAX_EXP) * (EXP_TABLE_SIZE / MAX_EXP / 2))]) * alpha;
                    for (c = 0; c < layer1_size; c++) neu1e[c] += g * syn1neg[c + l2];
                    for (c = 0; c < layer1_size; c++) syn1neg[c + l2] += g * syn0[c + l1];
                }
                // Learn weights input -> hidden
                for (c = 0; c < layer1_size; c++) syn0[c + l1] += neu1e[c];
            }
        }
        sentence_position++;
        if (sentence_position >= sentence_length) {
            sentence_length = 0;
            continue;
        }
    }
    fclose(fi);
    free(neu1);
    free(neu1e);
    pthread_exit(NULL);
}


void TrainModel() {
    long a, b, c, d;
    FILE *fo;
    // �������߳�
    pthread_t *pt = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    printf("Starting training using file %s\n", train_file);
    starting_alpha = alpha;
    // ���ȴӴʻ���ļ��м��أ������ѵ���ļ��м���
    if (read_vocab_file[0] != 0) ReadVocab(); else LearnVocabFromTrainFile();
    // ����ʻ���ļ�����+��Ƶ
    if (save_vocab_file[0] != 0) SaveVocab();
    if (output_file[0] == 0) return;
    InitNet(); // ����ṹ��ʼ��
    if (negative > 0) InitUnigramTable(); // ���ݴ�Ƶ���ɲ���ӳ��
    start = clock(); // ��ʼ��ʱ
    for (a = 0; a < num_threads; a++) pthread_create(&pt[a], NULL, TrainModelThread, (void *)a);
    for (a = 0; a < num_threads; a++) pthread_join(pt[a], NULL);

    // ѵ��������׼�����
    fo = fopen(output_file, "wb");

    if (classes == 0) { // ���� word vectors
        // Save the word vectors
        fprintf(fo, "%lld %lld\n", vocab_size, layer1_size); // �ʻ�����vectorά��
        for (a = 0; a < vocab_size; a++) {
            fprintf(fo, "%s ", vocab[a].word);
            if (binary) for (b = 0; b < layer1_size; b++) fwrite(&syn0[a * layer1_size + b], sizeof(real), 1, fo);
            else for (b = 0; b < layer1_size; b++) fprintf(fo, "%lf ", syn0[a * layer1_size + b]);
            fprintf(fo, "\n");
        }
    } else {
        // Run K-means on the word vectors
        // ����K-means�㷨
        int clcn = classes, iter = 10, closeid;
        int *centcn = (int *)malloc(classes * sizeof(int));
        int *cl = (int *)calloc(vocab_size, sizeof(int));
        real closev, x;
        real *cent = (real *)calloc(classes * layer1_size, sizeof(real));
        for (a = 0; a < vocab_size; a++) cl[a] = a % clcn;
        for (a = 0; a < iter; a++) {
            for (b = 0; b < clcn * layer1_size; b++) cent[b] = 0;
            for (b = 0; b < clcn; b++) centcn[b] = 1;
            for (c = 0; c < vocab_size; c++) {
                for (d = 0; d < layer1_size; d++) cent[layer1_size * cl[c] + d] += syn0[c * layer1_size + d];
                centcn[cl[c]]++;
            }
            for (b = 0; b < clcn; b++) {
                closev = 0;
                for (c = 0; c < layer1_size; c++) {
                    cent[layer1_size * b + c] /= centcn[b];
                    closev += cent[layer1_size * b + c] * cent[layer1_size * b + c];
                }
                closev = sqrt(closev);
                for (c = 0; c < layer1_size; c++) cent[layer1_size * b + c] /= closev;
            }
            for (c = 0; c < vocab_size; c++) {
                closev = -10;
                closeid = 0;
                for (d = 0; d < clcn; d++) {
                    x = 0;
                    for (b = 0; b < layer1_size; b++) x += cent[layer1_size * d + b] * syn0[c * layer1_size + b];
                    if (x > closev) {
                        closev = x;
                        closeid = d;
                    }
                }
                cl[c] = closeid;
            }
        }
        // Save the K-means classes
        for (a = 0; a < vocab_size; a++) fprintf(fo, "%s %d\n", vocab[a].word, cl[a]);
        free(centcn);
        free(cent);
        free(cl);
    }
    fclose(fo);
}

int ArgPos(char *str, int argc, char **argv) {
    int a;
    for (a = 1; a < argc; a++) if (!strcmp(str, argv[a])) {
        if (a == argc - 1) {
            printf("Argument missing for %s\n", str);
            exit(1);
        }
        return a;
    }
    return -1;
}

int main(int argc, char **argv) {
    int i;
    if (argc == 1) {
        printf("WORD VECTOR estimation toolkit v 0.1b\n\n");
        printf("Options:\n");
        printf("Parameters for training:\n");
        printf("\t-train <file>\n"); // ָ��ѵ���ļ�
        printf("\t\tUse text data from <file> to train the model\n");
        printf("\t-output <file>\n"); // ָ������ļ����Դ洢word vectors�����ߵ�����
        printf("\t\tUse <file> to save the resulting word vectors / word clusters\n");
        printf("\t-size <int>\n"); // word vector��ά������Ӧ layer1_size��Ĭ����100
        printf("\t\tSet size of word vectors; default is 100\n");
        // ���ڴ�С����cbow�б�ʾ��word vector�����ĵ��ӷ�Χ����skip-gram�б�ʾ��max space between words��w1,w2,p(w1 | w2)��
        printf("\t-window <int>\n");
        printf("\t\tSet max skip length between words; default is 5\n");
        printf("\t-sample <float>\n"); // �ǲ����ܾ����ʵĲ���
        printf("\t\tSet threshold for occurrence of words. Those that appear with higher frequency");
        printf(" in the training data will be randomly down-sampled; default is 0 (off), useful value is 1e-5\n");
        printf("\t-hs <int>\n"); // ʹ��hs��⣬Ĭ��Ϊ1
        printf("\t\tUse Hierarchical Softmax; default is 1 (0 = not used)\n");
        printf("\t-negative <int>\n"); // ʹ��ns��ʱ�������������
        printf("\t\tNumber of negative examples; default is 0, common values are 5 - 10 (0 = not used)\n");
        printf("\t-threads <int>\n"); // ָ���߳���
        printf("\t\tUse <int> threads (default 1)\n");
        printf("\t-min-count <int>\n"); // ��β�ʵĴ�Ƶ��ֵ
        printf("\t\tThis will discard words that appear less than <int> times; default is 5\n");
        printf("\t-alpha <float>\n"); // ��ʼ��ѧϰ���ʣ�Ĭ��Ϊ0.025
        printf("\t\tSet the starting learning rate; default is 0.025\n");
        printf("\t-classes <int>\n"); // ��������������Ĭ��Ϊ0��Ҳ�������������
        printf("\t\tOutput word classes rather than word vectors; default number of classes is 0 (vectors are written)\n");
        printf("\t-debug <int>\n"); // ���Եȼ���Ĭ��Ϊ2
        printf("\t\tSet the debug mode (default = 2 = more info during training)\n");
        printf("\t-binary <int>\n"); // �Ƿ񽫽�����Ϊ�������ļ���Ĭ��Ϊ0���������Ϊ������
        printf("\t\tSave the resulting vectors in binary moded; default is 0 (off)\n");
        printf("\t-save-vocab <file>\n"); // �ʻ���洢�ļ�
        printf("\t\tThe vocabulary will be saved to <file>\n");
        printf("\t-read-vocab <file>\n"); // �ʻ�������ļ�������Բ�ָ��trainfile
        printf("\t\tThe vocabulary will be read from <file>, not constructed from the training data\n");
        printf("\t-cbow <int>\n"); // ʹ��cbow���
        printf("\t\tUse the continuous bag of words model; default is 0 (skip-gram model)\n");
        printf("\nExamples:\n"); // ʹ��ʾ��
        printf("./word2vec -train data.txt -output vec.txt -debug 2 -size 200 -window 5 -sample 1e-4 -negative 5 -hs 0 -binary 0 -cbow 1\n\n");
        return 0;
    }
    // �ļ�������
    output_file[0] = 0;
    save_vocab_file[0] = 0;
    read_vocab_file[0] = 0;
    // ����������Ķ�Ӧ��ϵ
    if ((i = ArgPos((char *)"-size", argc, argv)) > 0) layer1_size = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-train", argc, argv)) > 0) strcpy(train_file, argv[i + 1]);
    if ((i = ArgPos((char *)"-save-vocab", argc, argv)) > 0) strcpy(save_vocab_file, argv[i + 1]);
    if ((i = ArgPos((char *)"-read-vocab", argc, argv)) > 0) strcpy(read_vocab_file, argv[i + 1]);
    if ((i = ArgPos((char *)"-debug", argc, argv)) > 0) debug_mode = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-binary", argc, argv)) > 0) binary = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-cbow", argc, argv)) > 0) cbow = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-alpha", argc, argv)) > 0) alpha = atof(argv[i + 1]);
    if ((i = ArgPos((char *)"-output", argc, argv)) > 0) strcpy(output_file, argv[i + 1]);
    if ((i = ArgPos((char *)"-window", argc, argv)) > 0) window = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-sample", argc, argv)) > 0) sample = atof(argv[i + 1]);
    if ((i = ArgPos((char *)"-hs", argc, argv)) > 0) hs = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-negative", argc, argv)) > 0) negative = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-threads", argc, argv)) > 0) num_threads = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-min-count", argc, argv)) > 0) min_count = atoi(argv[i + 1]);
    if ((i = ArgPos((char *)"-classes", argc, argv)) > 0) classes = atoi(argv[i + 1]);

    vocab = (struct vocab_word *)calloc(vocab_max_size, sizeof(struct vocab_word));
    vocab_hash = (int *)calloc(vocab_hash_size, sizeof(int));
    expTable = (real *)malloc((EXP_TABLE_SIZE + 1) * sizeof(real));
    // ����e^-6 �� e^6 ֮���fֵ
    for (i = 0; i < EXP_TABLE_SIZE; i++) {
        expTable[i] = exp((i / (real)EXP_TABLE_SIZE * 2 - 1) * MAX_EXP); // Precompute the exp() table
        expTable[i] = expTable[i] / (expTable[i] + 1);                   // Precompute f(x) = x / (x + 1)
    }
    TrainModel();
    return 0;
}