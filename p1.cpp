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

	// vector<int> small_graph_nodes;
	// vector<int> big_graph_nodes;

	int max_small = 0;
	int max_big = 0;
     
    // reading bigger graph 
    while (getline(fin, line)) { 
        stringstream iss( line );
        int f,s;
        iss >> f >> s;
        if(f>max_big)
        	max_big = f;
        if(s>max_big)
        	max_big = s;
        if(f == 0 && s == 0){break;}

        // big_graph_nodes.push_back(f);
        // big_graph_nodes.push_back(s);
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

    // reading smaller graph
    while (getline(fin, line)) { 
        stringstream iss( line );
        int f,s;
        iss >> f >> s;
        if(f>max_small)
        	max_small = f;
        if(s>max_small)
        	max_small = s;
        // small_graph_nodes.push_back(f);
        // small_graph_nodes.push_back(s);
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



 //    sort( small_graph_nodes.begin(), small_graph_nodes.end() );
	// small_graph_nodes.erase( unique( small_graph_nodes.begin(), small_graph_nodes.end() ), small_graph_nodes.end() );

	// sort( big_graph_nodes.begin(), big_graph_nodes.end() );
	// big_graph_nodes.erase( unique( big_graph_nodes.begin(), big_graph_nodes.end() ), big_graph_nodes.end() );

    // cout << 1 << endl;

    // size_sg = small_graph.size();
    // size_bg = big_graph.size();

    // for (auto itr = big_graph[200].begin(); itr != big_graph[200].end();itr++){
    // 	cout << *itr << ' ' ;
    // }
    // cout << endl;

    // cout << big_graph.size() << endl;
    // cout << small_graph.size() << endl;

    cout << max_small << ' '<< max_big << endl; 
    

    unordered_set<int> notposs;
    
    for (int i = 1; i <= max_small ; ++i){
    	for (int j = 1; j <= max_big ; ++j){
    		if( big_graph[j].size() < small_graph[i].size() || big_graph_in[j].size() < small_graph_in[i].size() ){
				notposs.insert(codify(i,j));		
    		}
    	}
    }

    cout << "notposs size: " << notposs.size() << endl;

    for (int zz = 1; zz <= 9*small_graph.size(); ++zz){
    	int i = zz%max_small;
    	for (int j = 1; j <= big_graph.size(); ++j){
    		vector<int> ilist;
    		vector<int> jlist;    		
    		std::copy(small_graph[i].begin(), small_graph[i].end(), std::back_inserter(ilist));
    		std::copy(big_graph[j].begin(), big_graph[j].end(), std::back_inserter(jlist));
    		int leni = ilist.size();
    		int lenj = jlist.size();
    		if(notposs.find(codify(i, j)) == notposs.end() && lenj < 40 && leni <=20){
    			unordered_set<int> onlyone;
    			for (int x = 0; x < leni; ++x){
    				set<int> y;
    				for (int m = 0; m < lenj; ++m){
    					if(notposs.find(codify(ilist[x], jlist[m]) ) == notposs.end() && onlyone.find(jlist[m]) == onlyone.end()){
    						y.insert(jlist[m]);
    					}
    				}
    				if(y.size() == 0){
    					notposs.insert(codify(i,j));
    					break;
    				}
    				if(y.size() == 1){
    					auto it = prev(y.end());
    					onlyone.insert(*it);
    					y.erase(it);
    				}
    			}
			}
    	}
    }

    cout << "notposs size: " << notposs.size() << endl;
			

    // cout << big_graph_nodes.size() << endl;
    // cout << small_graph_nodes.size() << endl;

    // for (int i = 0; i < big_graph_nodes.size(); ++i){
    // 	cout << big_graph_nodes[i] << endl;
    // }

	ofstream fout;
    fout.open(outfile);

    fout << "p cnf " << big_graph.size()*small_graph.size() << ' ' << endl; // pending

 //    for (auto itr = small_graph_nodes.begin(); itr != small_graph_nodes.end(); itr++){
	//  	for (auto itr2 = big_graph_nodes.begin(); itr2 != big_graph_nodes.end(); itr2++){
	//  		if(notposs.find(codify(i,j)) == notposs.end())
	//  			fout << codify(*itr, *itr2) << ' '; 
	//  	}
	//  	fout << 0 << endl;
	// }

    int temp1, temp2;
	for (int i = 1; i <= max_small; ++i){
	 	for (int j = 1; j <= max_big; ++j){
	 		temp1 = i;
	 		temp2 = j;
	 		// if(notposs.find(codify(temp1,temp2)) == notposs.end())
	 		fout << codify(temp1, temp2) << ' '; 
	 	}
	 	fout << 0 << endl;
	}

	cout << " Type 1 over" << endl;

	int t = 0;
	// int temp1, temp2;
	for (int k = 1; k <= max_small; ++k){
	 	for (int i = 1; i <= max_big; ++i){
	 		for (int j = i + 1; j <= max_big; ++j){ // possible place for error
	 			temp1 = codify(i,k);
	 			temp2 = codify(j,k);
	 			if(notposs.find(temp1) != notposs.end() || notposs.find(temp2) != notposs.end()){
	 				t++;
	 				fout << -1*temp1 << ' ' << -1*temp2 << ' ' << 0 << endl;
	 			}
	 		}
	 	}
	}

	cout << " Type 2.1 over" << endl; 

	for (int k = 1; k <= max_big; ++k){
	 	for (int i = 1; i <= max_small; ++i){
	 		for (int j = i + 1; j <= max_small; ++j){
	 			
	 			temp1 = codify(i,k);
	 			temp2 = codify(j,k);
	 			if(notposs.find(temp1) != notposs.end() || notposs.find(temp2) != notposs.end()){
	 				t++;
	 				fout << -1*temp1 << ' ' << -1*temp2 << ' ' << 0 << endl; 
	 			}
	 		}
	 	}
	} 

	cout << " Type 2.2 over" << endl;
	int tempx, tempy;
	for (auto itr : small_graph){
		temp1 = itr.first;
		for (auto itr2 = itr.second.begin(); itr2 != itr.second.end(); itr2++){
			for (int i = 1; i <= max_big; i++){
				for (int j = 1; j <= max_big; j++){
					if(big_graph.find(i) != big_graph.end() && big_graph[i].find(j) != big_graph[i].end()){
						continue;
					}
					else{
						tempx = codify(temp1, i);
						tempy = codify(*itr2, j);
						if(notposs.find(tempx) != notposs.end() || notposs.find(tempy) != notposs.end()){
							t++;
							fout << -1*tempx << ' ' << -1*tempy << ' ' << 0 << endl;
						}
					}
				}
			}
		}
	}

	cout << " Type 3.1 over" << endl;

	for (auto itr : big_graph){
		temp1 = itr.first;
		for (auto itr2 = itr.second.begin(); itr2 != itr.second.end(); itr2++){
			for (int i = 1; i <= max_small; i++){
				for (int j = 1; j <= max_small; j++){
					if(small_graph.find(i) != small_graph.end() && small_graph[i].find(j) != small_graph[i].end()){
						continue;
					}
					else{
						tempx = codify(temp1, i);
						tempy = codify(*itr2, j);
						if(notposs.find(tempx) != notposs.end() || notposs.find(tempy) != notposs.end()){
							t++;
							fout << -1*tempx << ' ' << -1*tempy << ' ' << 0 << endl;
						}
					}
				}
			}
		}
	}

	cout << " Type 3.2 over" << endl;

	cout << t << endl;


	// for (int i = 0; i < count; ++i){
	// 	/* code */
	// }

	fout.close();









	return 0;
}