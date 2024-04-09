//Your code begin.
//示例仅供参考，你也可以自行修改设计
#include<stdio.h>
#include<stdlib.h>
#include "string.h"
#define OK 1
#define ERROR 0
#define OVERFLOW -1


typedef struct ListNode            //结点结构，哈夫曼树与频度链表共用
{
    char      c;                    //结点的字符
    int      frequency;            // 字符的频度
    char     *code;            // 字符的编码(对哈夫曼树结点有效)
    struct ListNode *parent;            //结点的双亲结点(对哈夫曼树结点有效)
    struct ListNode *left;                //结点的左子树(对哈夫曼树结点有效)
    struct ListNode *right;                // 结点的右子树(对哈夫曼树结点有效)
    struct ListNode *next;                // 结点的后继结点(对频度链表结点有效)
}ListNode,HuffmanTree;



ListNode* InitList(){  //创造头节点
    ListNode* node=NULL;
    node= (ListNode*)malloc(sizeof(ListNode));
    if (!node) exit(OVERFLOW);
    node->c='\0';
    node->frequency=0;
    node->next=NULL;
    node->parent=NULL;
    node->left=NULL;
    node->right=NULL;
    node->code=NULL;
    return node;  //返回ok
}//end:InitList


ListNode* AddNode(ListNode* LastNode){    //在LastNode后添加结点
    ListNode* node=NULL;
    node=InitList();
    LastNode->next=node;
    return node;  //返回node
}//end:AddNode


void Search(char tem,ListNode* node){  //遍历频度链表结点，判断字符是否在其中
    while(node) {
        if (node->c == tem) {  //如果在该节点中的字符和给定字符相等，频度增加，返回1
            node->frequency++;
            return;
        } //end:if
        if(node->next==NULL) break;
        node=node->next;
    }//end:whlie
    node= AddNode(node);//在链中找不到含有字符tem的节点，创造新节点放在原有的后面
    node->c=tem;
    node->frequency=1;     //找不到字符 创造新节点，将频度设置为1

}//end:AlreadyIN


void GetFre(char*a,ListNode* head){    //遍历字符串输入，改变频度
    int i=0;
    while(a[i]!='\0'){   //遍历链表 调整频度
        Search(a[i++],head);
    }//end:while
}//end:GetFre

void Display(ListNode *node){   //展示频度
    while(node!=NULL){
        if(node->c=='\0') {
            node=node->next;
            continue; //排除头节点
        }
        if(node->c=='\n'){printf("\'\\n\' %d\n",node->frequency);}
        else {printf("\'%c\' %d %s\n",node->c,node->frequency,node->code);}
        node=node->next;
    }//end:while
}//end:Display

void Sort(ListNode*head) {  //排序    **对排序规则稍加修改，按照从小到大的顺序进行，便于建树**
    ListNode *first = head->next; //从头节点下一个开始
    ListNode *node = head->next; //从头节点下一个开始
    int TemFrequency;
    char TemChar;
    while (first) {
        while (node->next) {
            if (node->next->frequency < node->frequency) {  //交换数据域
                TemFrequency = node->frequency;
                TemChar = node->c;
                node->frequency = node->next->frequency;
                node->c = node->next->c;
                node->next->frequency = TemFrequency;
                node->next->c = TemChar;
            }
            node = node->next;
        }
        node = head->next;
        first = first->next;
    }
}//end:sort

int HasNoParents(ListNode*head){  //判断是否有父母结点
    head=head->next;   //跳过头节点
    while (head->next!=NULL) {  //遍历链表，判断是否有父母结点
        if(head->parent==NULL) return 1;
        head=head->next;
    }
}//end:HasParents

ListNode* InsertNode(ListNode*LC,ListNode*RC,ListNode*head){  //按照频度顺序插入结点
    int fre=LC->frequency+RC->frequency;
    while(head->next==NULL||head->next->frequency<=fre) head=head->next; //由于整个链表是按照顺序排列，只需在下一个结点的频度大于此节点的频度时插入即可
    ListNode *parents;  //创造双亲结点
    parents=InitList();
    parents->frequency=fre;    //双亲节点初始化
    parents->right=RC;
    parents->left=LC;
    ListNode *tem=head->next;  //插入节点
    head->next=parents;
    parents->next=tem;
    return parents;
}

void CreateTree(ListNode* head){  //创造树结点
    ListNode * LChild=head->next;
    ListNode * RChild;
    while(HasNoParents(head)){
        while(LChild->parent) LChild=LChild->next;   //整个链表按顺序存储，只需要选取最靠前的两个没有父母结点的即可
        RChild=LChild->next; //RChild从LChild的下一个开始查找
        while(RChild->parent) {
            RChild=RChild->next;
            if(RChild==NULL) return;  //如果此时Rchild遍历到最后依然找不到。说明仅剩下一个未有父母节点的节点，即根节点 此时返回
        }
        ListNode*par=InsertNode(LChild,RChild,head);
        RChild->parent=par;
        LChild->parent=par;

    }
}//end:CreateTree     //在此时，树中只有两个没有父母节点的节点，即为根节点与头节点

ListNode *GetRoot(ListNode*head){//获取哈夫曼树的根节点
    head=head->next;   //跳过头节点
    while(head){
        if(head->parent==NULL) return head;
        head=head->next;
    }
}


void GetHuffmanCode(ListNode* root, char* code, int depth) {
    if (root->left == NULL && root->right == NULL) {
        root->code = (char*)malloc((depth + 1) * sizeof(char));
        strcpy(root->code, code);
        return;
    }

    code[depth] = '0';
    code[depth + 1] = '\0';
    GetHuffmanCode(root->left, code, depth + 1);

    code[depth] = '1';
    code[depth + 1] = '\0';
    GetHuffmanCode(root->right, code, depth + 1);
}


int main() {
    ListNode *head = NULL;
    head = InitList();
    char code[100];
    code[0]='\0';
    char str[1000];
    char tem;
    int i = 0;
    while ((tem = getchar()) != EOF) {
          str[i++] = tem;
    }
  str[i]='\0';
    GetFre(str, head);
    Sort(head);
    CreateTree(head);
    GetHuffmanCode(GetRoot(head),code,0);
    Display(head);
    return 0;
}
//Your code end.