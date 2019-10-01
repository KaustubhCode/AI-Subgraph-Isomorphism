#include <bits/stdc++.h>
#include <chrono>
using namespace std;

int codify(int small, int big){
	int e = small + big;
	return e*(e + 1)/2 + big;
}

vector<int> decodify(int code){

	int w = ( sqrt(8*code + 1) - 1 )/2;
	int t = w*(w + 1)/2;
	int y = code - t;
	int x = w - y;

	vector<int> v;
	v.push_back(x);
	v.push_back(y);
	return v;
}

int main(int argc, char const *argv[]){
	
	string filename = argv[1];
	string infile = filename + ".graphs";
	string outfile = filename + ".satinput";


	string line;

    ifstream fin; 
    fin.open(infile);
	
	unordered_map<int, unordered_set<int>> small_graph;// to vector
	unordered_map<int, unordered_set<int>> big_graph; // to vector
	unordered_map<int, unordered_set<int>> small_graph_in;// to vector
	unordered_map<int, unordered_set<int>> big_graph_in;   // to vector
     
    while (getline(fin, line)) { 
        stringstream iss( line );
        int f,s;
        if(f == 0 && s == 0){break;}
        iss >> f >> s;

        if(big_graph.find(f) == big_graph.end()){
        	big_graph[f] = {s};
        }
        else{
        	big_graph[f].insert(s);
        }
        if(big_graph_in.find(s) == big_graph_in.end()){
        	big_graph_in[s] = {f};
        }
        else{
        	big_graph_in[s].insert(f);
        }
    } 

    while (getline(fin, line)) { 
        stringstream iss( line );
        int f,s;
        iss >> f >> s;

        if(small_graph.find(f) == small_graph.end()){
        	small_graph[f] = {s};
        }
        else{
        	small_graph[f].insert(s);
        }
        if(small_graph_in.find(s) == small_graph_in.end()){
        	small_graph_in[s] = {f};
        }
        else{
        	small_graph_in[s].insert(f);
        }
    } 
    fin.close();
    cout << 1 << endl;

    // size_sg = small_graph.size();
    // size_bg = big_graph.size();

    // for (auto itr = big_graph[200].begin(); itr != big_graph[200].end();itr++){
    // 	cout << *itr << ' ' ;
    // }
    // cout << endl;

    cout << big_graph.size() << endl;
    cout << small_graph.size() << endl;
    

    unordered_set<int> notposs;

    for (int i = 1; i <= small_graph.size(); ++i){
    	for (int j = 1; j <= big_graph.size(); ++j){
    		//if( big_graph[j].size() < small_graph[i].size() || big_graph_in[j].size() < small_graph_in[i].size() ){
			//	notposs.insert(codify(i,j));		
    		//}
    	}
    }
			

    cout << big_graph.size() << endl;
    cout << small_graph.size() << endl;

	ofstream fout;
    fout.open(outfile);

    fout << "p cnf " << big_graph.size()*small_graph.size() << ' ' << endl; // pending

	for (int i = 1; i <= small_graph.size(); ++i){
	 	for (int j = 1; j <= big_graph.size(); ++j){
	 		if(notposs.find(codify(i,j)) == notposs.end())
	 			fout << codify(i, j) << ' '; 
	 	}
	 	fout << 0 << endl;
	}

	cout << " Type 1 over" << endl;

	int t = 0;
	int temp1, temp2;
	for (int k = 1; k <= small_graph.size(); ++k){
	 	for (int i = 1; i <= big_graph.size(); ++i){
	 		for (int j = i + 1; j <= big_graph.size(); ++j){
	 			t ++;
	 			temp1 = codify(i,k);
	 			temp2 = codify(j,k);
	 			if(notposs.find(temp1) == notposs.end() && notposs.find(temp2) == notposs.end())
	 				fout << -1*temp1 << ' ' << -1*temp2 << ' ' << 0 << endl;
	 		}
	 	}
	}

	cout << " Type 2.1 over" << endl; 

	for (int k = 1; k <= big_graph.size(); ++k){
	 	for (int i = 1; i <= small_graph.size(); ++i){
	 		for (int j = i + 1; j <= small_graph.size(); ++j){
	 			t++;
	 			temp1 = codify(i,k);
	 			temp2 = codify(j,k);
	 			if(notposs.find(temp1) == notposs.end() && notposs.find(temp2) == notposs.end())
	 				fout << -1*temp1 << ' ' << -1*temp2 << ' ' << 0 << endl; 
	 		}
	 	}
	} 

	cout << " Type 2.2 over" << endl;

	cout << t << endl;

	fout.close();









	return 0;
}