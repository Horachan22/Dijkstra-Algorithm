/*
===================================================================
Project Name  : コンピュータネットワーク 期末レポート (1)必修課題 ダイクストラ法
File Name     : dijkstra.hpp
Encoding      : UTF-8
Creation Date : 4/8/2021
Copyright (c) 2021 Yuma Horaguchi All rights reserved.
===================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// ノードのクラス
class Node{
	public:
		int node_name;
		bool checker;
		vector<Node*> connected_node;
		vector<int>   connected_distance;
		// コンストラクタ
		Node(){}
		Node(int node_name){
			this -> node_name = node_name;
			this -> checker = false;
		}
};

// ダイクストラ法の表のクラス
class Dijkstra_Table{
	public:
		vector<Node*> node_list;
		vector<int>   node_dist_list;
		vector<Node*> prev_node;

		// デストラクタ
		~Dijkstra_Table(){
			for(vector<Node*>::iterator it = node_list.begin(); it != node_list.end(); it++){
				delete *it;
			}
		}

		// 表の初期状態を作成する関数
		vector<Node*> make_table(vector< vector<int> > list_data){
			for(int i = 0; i < list_data[0][1]; i++){
				Node* add_node = new Node(i);
				node_list.push_back(add_node);
				node_dist_list.push_back(INT32_MAX);
				prev_node.push_back(nullptr);
			}
			return node_list;
		}

		// ダイクストラ法
		void dijkstra(vector<Node*> node_list, int start){
			node_dist_list[start] = 0;
			queue<int> next_node;
			while (!checked()){
				for(int i = 0; i < node_list[start] -> connected_node.size(); i++){
					Node* connection = node_list[start] -> connected_node[i];
					int distance = node_dist_list[start] + node_list[start] -> connected_distance[i];
					if(node_dist_list[connection -> node_name] > distance){
						node_dist_list[connection -> node_name] = distance;
						prev_node[connection -> node_name] = node_list[start];
						// 後から最短経路が見つかった場合
						connection -> checker = false;
					}
					if(!connection -> checker){
						next_node.push(connection -> node_name);
					}
				}
				// ノード処理終了
				node_list[start]->checker = true;
				start = next_node.front();
				next_node.pop();
			}
		}

		// ノードの処理が終了したか判定する関数
		bool checked(){
			for(int i = 0; i < node_list.size(); i++){
				if(node_list[i]->checker == false){
					return false;
				}
			}
			return true;
		}

		// ダイクストラの表を表示する関数
		void print_table(){
			for(int i = 0; i < node_list.size(); i++){
				if (prev_node[i] != nullptr){
					cout << node_list[i] -> node_name << " "<< node_dist_list[i] << " " << prev_node[i] -> node_name << endl;
				}
				else{
					cout << node_list[i] -> node_name << " "<< node_dist_list[i] << " " << "NULL" << endl;
				}
			}
		}

		// 最短経路を出力する関数
		void print_ans(int start, int goal){
			vector<int> ans;
			cout << "経路：" << start;

			for(int i = goal; prev_node[i] != nullptr; i = prev_node[i]->node_name){
				ans.push_back(i);
			}

			for(vector<int>::reverse_iterator it = ans.rbegin(); it != ans.rend(); it++){
				cout << "->" << *it;
			}
			cout << "　総コスト：" << node_dist_list[goal] << endl;
		}
};

// ある行lineを文字key_strでsplitする関数(今回txtファイルから読み込むのでkey_str = " ")
vector<int> split(string line, string key_str){
	int start = 0;
	int key_place = line.find_first_of(key_str);
	vector<int> splited_line;
	// Key_strの前の文字までを抽出
	while(start < line.size()){
		string substr = line.substr(start, key_place - start);
		splited_line.push_back(stoi(substr));
		start = key_place + 1;
		key_place = line.find_first_of(key_str, start);
		if(key_place == string::npos){
			key_place = line.size();
		}
	}
	return splited_line;
}

// txtファイルを2次元配列に変換、格納する関数
vector<vector<int> > make_list(string filename){
	ifstream file;
	file.open(filename, ios_base::in);
	vector<vector<int> > list_data;
	string line;
	// ファイルが存在しなかったとき
	if(!file){
		exit(EXIT_FAILURE);
	}
	// 2次元配列の生成
	while(getline(file, line)){
		if(line.size() == 0){
			break;
		}
		vector<int> splited_line = split(line, " ");
		list_data.push_back(splited_line);
	}
	file.close();
	return list_data;
}

// Nodeに接続情報を格納する関数
void set_connected_data(vector< vector<int> > list_data, vector<Node*> node_list){
	for(int i = 0; i < node_list.size(); i++){
		for(int j = 1; j < list_data.size(); j++){
			if(node_list[i] -> node_name == list_data[j][0]){
				node_list[i] -> connected_node.push_back(node_list[list_data[j][1]]);
				node_list[i] -> connected_distance.push_back(list_data[j][2]);
			}
			else if(node_list[i] -> node_name == list_data[j][1]){
				node_list[i] -> connected_node.push_back(node_list[list_data[j][0]]);
				node_list[i] -> connected_distance.push_back(list_data[j][2]);
			}
		}
	}
}
