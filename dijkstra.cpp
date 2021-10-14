/*
===================================================================
Project Name  : コンピュータネットワーク 期末レポート (1)必修課題 ダイクストラ法
File Name     : dijkstra.cpp
Encoding      : UTF-8
Creation Date : 4/8/2021
Copyright (c) 2021 Yuma Horaguchi All rights reserved.
===================================================================
*/

#include "dijkstra.hpp"

int main(int argc, char *argv[]){
	Dijkstra_Table table;
	vector< vector<int> > list_data = make_list(argv[1]);
	vector<Node*> node_list = table.make_table(list_data);
	set_connected_data(list_data, node_list);
	int start_num;
	int goal_num;
	cout << "出発ノードの番号を入力：";
	cin >> start_num;
	cout << "目的ノードの番号を入力：";
	cin >> goal_num;
	table.dijkstra(node_list, start_num);
	table.print_table();
	table.print_ans (start_num, goal_num);
}
