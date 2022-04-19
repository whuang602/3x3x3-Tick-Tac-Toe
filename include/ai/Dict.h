#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

template<class KeyType, class ValueType>
class Dict {
	public:
		ValueType get(KeyType key){
			for(int i = 0; i < keys.size(); i++){
				if(keys[i] == key){
					return values[i];
				}
			}
			//return 0;
			cerr << "key not found" << endl;
			exit(1);	
		}

		void set(KeyType key, ValueType value) {
			for(int i = 0; i < keys.size(); i++){
				if(keys[i] == key){
					values[i] = value;
				}
			}
		}

		pair<KeyType, ValueType> index_get(int index){
			pair<KeyType, ValueType> p = {keys[index], values[index]};
			return p;
		}
	
		bool has_key(KeyType key){
			for(int i = 0; i < keys.size(); i++){
				if(keys[i] == key){
					return true;
				}
			}
			return false;
		}

		void add(KeyType key, ValueType val){
			keys.push_back(key);
			values.push_back(val);
		}

		int size(){
			return keys.size();
		}

		void empty(){
			keys = {};
			values = {};
		}

	private:
		vector<KeyType> keys;
		vector<ValueType> values;
};

/*
   struct Move {
   string add_rem;
   int x;
   int y;
   bool operator==(const Move& other) const {
   return (add_rem == other.add_rem) &&
   (x == other.x) && (y == other.y);
   }
   };

   int main(){
   vector<int> dv = {0, 1};
   Move dm = {"ADD", 0, 0};
   dict<vector<int>, double> my_dict1;
   my_dict1.add(dv, 10);
   dict<Move, vector<int> > my_dict2;
   my_dict2.add(dm, dv);

   return 0;
   }
 */
