
#include "heap.h"
#include "shortestPath.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int load_file(char* fname,int (*link_state_packet)[MAXNODES],int& router_cnt)
{
	char data;
	int i,j;
	int row=0,col=0; //initialize routing table row and column

	ifstream i_file(fname);

	if(i_file.fail()){
		printf("Original routing table not found!\n");
		return 0;
	} 

	while(i_file.good()){
		char data = i_file.get();	
		if(data == '-'){     //replace '-' with -1 value			
			link_state_packet[row][col]= -1;
			data=i_file.get();  //discard next character in the file
			col++;
		}

		else if(data == '\n'){  //end line character, so just increase the row value to reach new row
			row++;
			col = 0;
		}
				
		else if(data > 47 && data < 58)       //store original routing table data in the array for futher process
			link_state_packet[row][col++] = data - 48;

	}

	i_file.close();	

	row--;   //discard the line of character 0 which means end of file
	router_cnt = col = row;

	//print original routing table
	for(i=0;i <= row;i++){
		for(j=0;j <= col;j++){
			cout << setw(3) << link_state_packet[i][j];
		}
		cout << "\n";
	}

	return 1;
}

int menu()
{
	int choice;
	
	cout << "\n*Implementation of Link-State Routing Protocol*";
	cout << "\n==============================================\n";
	cout << "1-Load File\n"
	     << "2-Build Routing Table for Each Router\n"
	     << "3-Out Optimal Path and Minimum Cost\n"
	     << "0-Exit Program\n";
	cout << "==============================================\n";
	cout << "Choose operation(Enter option number):";

	cin >> choice;
	cin.ignore();

	return choice;
}

int main(){
	char fname[50];
	int link_state_packet[MAXNODES][MAXNODES];
	int router_cnt;
	int source,destination,choice;
	int LSP=0;
	Path path;

	do{
		choice = menu();
		switch(choice)
		{
			case 1:
				//loading original routing table file
				cout << "Please load original routing table data file:\n";
				cin.get (fname,50);
				LSP = load_file(fname,link_state_packet,router_cnt);

				cout << "\n";
				break;
			case 2: 
				//calculate optimal routing table for given source
				if(!LSP){   //didn't load original routing table
					cout << "LSP not found!\n";
					break;
				}

				cout << "Please select a router:\n";
				cin >> source;
				if(source-1 > router_cnt)
				{
					cout << "Input router does not existing!\n";
					break;	
				}

				path.shortest_path(source,0,router_cnt,link_state_packet);   //calculate optimal routing table for source router

				break;
			case 3:
				//calculate shortest path for given two routers
				if(!LSP){   //didn't load original routing table

                                        cout << "LSP not found!\n";
                                        break;
                                }

				cout << "Please input the source and the destination router number:\n";
			        cin >> source >> destination;
				if(source-1 > router_cnt || destination-1 > router_cnt)
				{
					cout << "Source or destination does not existing!\n";
					break;	
				}

				path.shortest_path(source,destination,router_cnt,link_state_packet);  //caculate shortest path from source to destination

				break;
			case 0:
				break;
			default :
				cout << "Choose operation from 0~3\n";
		}
	}while(choice != 0);
		

	return 0;
}

