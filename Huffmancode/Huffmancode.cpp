
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <queue>
#include <vector>



using namespace std;
int line=0;
int k=0;
int m=0;
typedef struct TreeNode                                     //定義樹的節點內容
{
    int freq;
    char data;
    TreeNode *left, *right;
    TreeNode(char data, int freq)
    {
        this->freq = freq;
        this->data = data;
        left = right = NULL;


    }
} ;





void answer(struct TreeNode* root, string ans,ofstream &fout)           //這邊是從樹的下而上讀上去,不過答案一樣的應該
{
    if (!root)
        return;

    if (root->data != '\0')
    {

        fout<<root->data << ":" << ans<<"," ;
    }

    answer(root->right, ans + "1",fout);
    answer(root->left, ans + "0",fout);
}
struct compare
{
    bool operator()(TreeNode* left, TreeNode* right)
    {
        return (left->freq > right->freq);
    }
};
void huffman(char data[], int freq[], int size,ofstream &fout)
{
    struct TreeNode *left, *right, *top;                          //把每題資料讀進來後建樹,top是現在要建的節點位置
    priority_queue<TreeNode*, vector<TreeNode*>, compare> sorted;  //網上教的如何把資料讀進queue然後call compare把queue排序 :https://stackoverflow.com/questions/2439283/how-can-i-create-min-stl-priority-queue
    for (int i = 0; i < size; ++i)
        sorted.push(new TreeNode(data[i], freq[i]));                //現在push進去sorted的資料會由小到大排好


    while (sorted.size() != 1)
    {
        left = sorted.top();                                        //left跟 right現在會是最小的2個數字
        sorted.pop();

        right = sorted.top();
        sorted.pop();


        top = new TreeNode('\0', left->freq + right->freq);         //把他們+起來成為新節點,用\0來分辨他們不是原來讀入的資料(A,B,C..)
        top->left = left;
        top->right = right;
        sorted.push(top);
    }


    answer(sorted.top(), "", fout);                             //寫入資料


}







int main()
{
    fstream fin;
    ofstream fout;
    fin.open("input.txt",fstream::in);
    fout.open("output.txt",fstream::out|fstream::trunc);

    string serial;
    int b=0;
    int c=0;
    int d=0;
    int e=0;
    char letter[100];                                       //letter 讀input.txt的字母
    int number[100];                                        //number 讀input.txt的數字
    while(getline(fin,serial))
    {

        for(int a=0; a<serial.length(); a++)               //除了call huffman以外下面都是讀input.txt的方法
        {

            if(serial[a]==':')
            {
                letter[c]=serial[a-1];
                c++;
                a++;
            }
            if(serial[a]-'0'>=0&&serial[a]-'0'<=9)
            {
                b*=10;
                b+=serial[a]-'0';
            }
            if(serial[a]==',')
            {

                number[d]=b;
                d++;
                b=0;

            }

        }
        number[d]=b;
        d++;
        b=0;



        huffman(letter, number, d,fout);
        fout<<"\n";
        d=0;
        c=0;
    }

    return 0;
}
