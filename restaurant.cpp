#include "restaurant.h"
// bool cmp (pair<char, int> p1, pair<char,int> p2){
// 	if(p1.second == p2.second) return p1.first < p2.first;
// 	return p1.second < p2.second;
// }
char caesarEncode(char ch, int shift) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return static_cast<char>((ch - base + shift) % 26 + base);
    } else {
        // If the character is not a letter, return it unchanged
        return ch;
    }
}
void assignCode(HuffNode* node, unordered_map<char, string>& huffCode, string temp){
	if(!node) return;
	if(node->isLeaf()){
		huffCode[((LeafNode*)node)->val()]= temp;
		return;
	}
	else{
		assignCode(((IntlNode*)node)->left(), huffCode, temp+'0');
		assignCode(((IntlNode*)node)->right(), huffCode, temp+'1');
	}
}
int getResult(string name, unordered_map<char, string> huffCode){
	string binaryString = "";
	for(int i=0; i<(int) name.size(); i++){
		binaryString += huffCode[name[i]];
	}
	int decimalNumber = 0;
	for(int i=binaryString.size() - 1; i>= binaryString.size()- 10 && i>= 0; i--){
		decimalNumber = decimalNumber* 2 + (binaryString[i]-'0');
	}
	return decimalNumber;
}
int LAPSE(string name){
	// Make the X list
	list < pair<char,int>> ll;
	unordered_map <char, int> cnt;
	for(int i=0; i<(int)name.size(); i++){
		if(cnt[name[i]] == 0){
			ll.push_back({name[i],0});
		}
		cnt[name[i]]++;
	}
	if(cnt.size() < 3) return -1;
	auto it = ll.begin();
	while(it != ll.end()){
		(*it).second = cnt[(*it).first];
		it++;
	}
	it = ll.begin();
	while(it != ll.end()){
		(*it).first = caesarEncode((*it).first, (*it).second);
		it++;
	}
	

	for(auto it = ll.begin();it != ll.end(); it++){	//mergeChar after caesar
		auto nextIt = it;
		nextIt++;
		for(auto it2 = nextIt; it2!= ll.end(); it2++){
			if((*it2).first == (*it).first){
				(*it).second+= (*it2).second;
				*it2 = {0,0};
			}
		}
		ll.remove({0,0});
	}
	auto cmp = [](pair<char, int> p1, pair<char,int> p2){if(p1.second == p2.second) return p1.first < p2.first;
	return p1.second < p2.second;};
	ll.sort(cmp);	// ll is now X list
	// for(auto item: ll){
	// 	cout<<item.first<<" "<<item.second<<endl;
	// }
	
	auto customCompare = [](HuffTree* a, HuffTree* b) { return a->root()->weight() > b->root()->weight(); };
	priority_queue <HuffTree*, vector<HuffTree*>, decltype(customCompare)>  forest(customCompare);	// BUILD HUFFMAN TREE
    for(auto item: ll){
        forest.push(new HuffTree(item.first, item.second));
    }
	/*******************************************/
	auto printHeap = [](priority_queue <HuffTree*, vector<HuffTree*>, decltype(customCompare)> heap){
		while(!heap.empty()){
			if(!heap.top()->root()->isLeaf()) cout<<"Int";
			cout<<heap.top()->weight()<<" ";
			heap.pop();
		}
		cout<<endl;
	};
	/*******************************************/
    HuffTree *temp1, *temp2, *temp3 = NULL;
    while (forest.size() > 1)
    {
        temp1 = forest.top(); // Pull first two trees
        forest.pop();
        temp2 = forest.top(); // off the list
        forest.pop();
        temp3 = new HuffTree(temp1, temp2);
        forest.push(temp3); // Put the new tree back on list
        // delete temp1;          // Must delete the remnants
        // delete temp2;          // of the trees we created
		//printHeap(forest);
    }
	//temp3->print(temp3->root());
	unordered_map<char, string> huffCode;
	assignCode(temp3->root(), huffCode, "");
	int res = getResult(name, huffCode);
	return res;
	
}


void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;
	while(ss >> str){
		if(str == "MAXSIZE"){
			ss>>maxsize;
			MAXSIZE = stoi(maxsize);
		}
		else if(str == "LAPSE"){
			ss>>name;
			if(LAPSE(name) == -1){
				cout<<"Name to short"<<endl;
			}
		}
		else if(str =="KOKUSEN"){

		}
		else if(str == "KEITEIKEN"){
			ss>>num;

		}
		else if(str == "HAND"){

		}
		else if(str == "LIMITLESS"){
			ss >> num;
		}
		else if(str == "CLEAVE"){
			ss >> num;
		}
	}
	cout << "Good Luck";
	
	return;
}