#include <iostream>
#include <exception>
#include <opencv2\opencv.hpp>
#include <ctime>
#include <cstdlib>

#define ON_THE_BOARD 1
#define OFF_BOARD_BEFORE 2
#define OFF_BOARD_AFTER 3

using namespace std;
using namespace cv;

class STONE{
	public:
		int stone_id;
		int stone_pos;
		
	STONE::STONE(int stone_id){
		stone_id = stone_id;
		stone_pos = OFF_BOARD_BEFORE;
	}
};

class PLAYER{
	public:
		int player_id;
		int active_stones;
		std::list<STONE> stones = {};
		
	PLAYER::PLAYER(int player_id, int active_stones){
		this->player_id= player_id;
		this->active_stones = active_stones;
		
		for(int k=0; k<active_stones; k++){
			STONE mystone(k);
			stones.push_front(mystone);
		}
		srand(time(0));
	}
	
	int PLAYER::throw_dice(){
		int number = (rand()%2)+(rand()%2)+(rand()%2)+(rand()%2);
		return number;
	}
};

class MAP{
	public:
		int round_ctr;
		bool game_over;
		int m_height,m_width;
		int map[8][3] = {};
		
	MAP::MAP(){
		round_ctr = 0;
		game_over = false;
		
		m_height = 8;
		m_width = 3;
			
		map[4][0] = map[5][0] = map[4][2] = map[5][2] = -1;
	}
	
	void MAP::print(){
		printf("------------------- ROUND %d -------------------\n",round_ctr);
		for(int h=0;h<m_height;h++){
			printf(" ");
			for(int w=0;w<m_width;w++){
				int field_entry = map[h][w];
				if(field_entry>=0){
					printf("%d",field_entry);
				}else{
					printf(" ");
				}
			}
			printf("\n");
		}
		printf("-----------------------------------------------\n");
	}
};

int main(){
	
	int num_stones = 4;
	
	MAP gamemap;
	
	PLAYER p0(0,num_stones);
	PLAYER p1(1,num_stones);
	
	while(!gamemap.game_over){
		
		gamemap.print();
		
		int p0_number = p0.throw_dice();
		printf("Player %d throws a %d\n",p0.player_id,p0_number);
		
		int stone_id_p0;
		cout<<"The dice have been cast, player "<<p0.player_id<<", which stone would you like to move?"<<endl;
		cin>>stone_id_p0;
	}
	
	cout<<"Game has terminated, Sargon of Akkad has won the game!"<<endl;
	cin.get();
	return 0;
}
