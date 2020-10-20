#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

bool valid_sudoku(const std::vector<int>& g);
bool check_sequence(const std::vector<int>& v);
int mfind(int n, const std::vector<int>& v);

void get_row(int r, const std::vector<int>& in, std::vector<int>& out);
void get_col(int c, const std::vector<int>& in, std::vector<int>& out);
void get_subsq(int subs, const std::vector<int>& in, std::vector<int>& out);

int twod_to_oned(int row, int col, int rowlen);

int main(){
    
    std::vector<int> s;
    std::string filename;
    
    std::cout << "please enter name of file containing the sudoku" << std::endl;
    std::cin >> filename;
    
    std::ifstream infile;
    infile.open(filename.c_str());
    
    if(!infile.is_open()){
        std::cout << "error, can't open input file" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    int tmp;
    
    while(infile >> tmp){
        s.push_back(tmp);
    }
   
    int side = std::sqrt(s.size());
    
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            std::cout << s[twod_to_oned(i,j,side)] << " ";
        }
        std::cout << std::endl;
    }
    bool valid = valid_sudoku(s);
    
    if(valid){
        std::cout << "valid" << std::endl;
    }
    else{
        std::cout << "not valid" << std::endl; 
    }
}

int twod_to_oned(int row, int col, int rowlen){
    return row*rowlen+col;
}

bool valid_sudoku(const std::vector<int>& g){
    int side = std::sqrt(g.size()); 

    for(int i = 0; i < side; i++){
        std::vector<int> row;
        get_row(i, g, row);
        
        if(!check_sequence(row)){ 
            return false;
        }
    }
    
    for(int i = 0; i < side; i++){
        // write
        std::vector<int> col;
        get_col(i, g, col);

        if(!check_sequence(col)){
            return false;
        }
    }
    
    for(int i = 0; i < side; i++){
      // write
       std::vector<int> subsq;
       get_subsq(i, g, subsq);
       
       if(!check_sequence(subsq)){
           return false;
       }
    }
    return true;
}


int mfind(int n, const std::vector<int>& v){
    // write
    for(int i=0; i < v.size(); i++){
        if(v[i]==n){
            return i;
        }
    }
    return -1;
}


bool check_sequence(const std::vector<int>& v){
    // write
    for(int i=1; i <= v.size(); i++){
        if( mfind(i, v) == -1 ){
            return false;
        }
    }
    return true;
}


void get_row(int r, const std::vector<int>& in, std::vector<int>& out){
    // write
    int side = std::sqrt(in.size());
    
    for (int i=0; i < side; i++){
        out.push_back( in[twod_to_oned(r,i,side)] );
    }
}

void get_col(int c, const std::vector<int>& in, std::vector<int>& out){
    // write
    int side = std::sqrt(in.size());
    
    for (int i=0; i < side; i++){
        out.push_back( in[twod_to_oned(i,c,side)] );
    }
}


void get_subsq(int subs, const std::vector<int>& in, std::vector<int>& out){
    //write
    int side = std::sqrt(in.size());
    int subsize = std::sqrt(side);
    int starty = (subs * subsize) % side;
		/// a more straightfoward way could be 'std::floor(subs*subsize)/subsize',
		/// which saves one operation
    int startx = subsize * (( subs * subsize ) / side);
    
    for(int i=0; i < subsize; i++){
        for(int j=0; j < subsize; j++){
						/// no need for brackets in '(startx+i)' and '(starty+j)'
            out.push_back( in[twod_to_oned( (startx+i), (starty+j), side )]);
        }
    }
		/// nice implementation overall
}
