#include <iostream>
#include <vector>
using namespace std;

struct  children
{
	long long  need;
	long long  have;
};

int main() {
	int n,s;
	while(cin >> n >> s && n != 0) {
 		int i;
 		long long a,b;
 		bool flag = true;
		vector<children> lego;
		lego.clear();
 		for(i = 0; i < n; i++) {
 			children tmp;
 			cin >> a >> b;
 			if( s >= b) {
 				s += a;
 				continue;
 			} else {
	 			tmp.have = a;
	 			tmp.need = b;
	 			lego.push_back(tmp);
	 		}
 		}
 		vector<children>::iterator it;
 		while(flag) {
 			if(!lego.empty()) {
	 			flag = false;
	 			for(it = lego.begin(); it != lego.end();) {
	 				if(s >= (*it).need) {
	 					s += (*it).have;
	 					it = lego.erase(it);
	 					flag = true;
	 				} else {
		 				it++;
		 			}
	 			}
 			} else {
 				flag = true;
 				break;
 			}
 		}
 		flag ? cout << "YES" << endl : cout << "NO" << endl;
	}
	return 0;
}
