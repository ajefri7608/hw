
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
typedef struct TreeNode                                     //�w�q�𪺸`�I���e
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





void answer(struct TreeNode* root, string ans,ofstream &fout)           //�o��O�q�𪺤U�ӤWŪ�W�h,���L���פ@�˪�����
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
    struct TreeNode *left, *right, *top;                          //��C�D���Ū�i�ӫ�ؾ�,top�O�{�b�n�ت��`�I��m
    priority_queue<TreeNode*, vector<TreeNode*>, compare> sorted;  //���W�Ъ��p�����Ū�iqueue�M��call compare��queue�Ƨ� :https://stackoverflow.com/questions/2439283/how-can-i-create-min-stl-priority-queue
    for (int i = 0; i < size; ++i)
        sorted.push(new TreeNode(data[i], freq[i]));                //�{�bpush�i�hsorted����Ʒ|�Ѥp��j�Ʀn


    while (sorted.size() != 1)
    {
        left = sorted.top();                                        //left�� right�{�b�|�O�̤p��2�ӼƦr
        sorted.pop();

        right = sorted.top();
        sorted.pop();


        top = new TreeNode('\0', left->freq + right->freq);         //��L��+�_�Ӧ����s�`�I,��\0�Ӥ���L�̤��O���Ū�J�����(A,B,C..)
        top->left = left;
        top->right = right;
        sorted.push(top);
    }


    answer(sorted.top(), "", fout);                             //�g�J���


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
    char letter[100];                                       //letter Ūinput.txt���r��
    int number[100];                                        //number Ūinput.txt���Ʀr
    while(getline(fin,serial))
    {

        for(int a=0; a<serial.length(); a++)               //���Fcall huffman�H�~�U�����OŪinput.txt����k
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
