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
    node= (ListNode*)malloc(sizeof(ListNode)); //申请空间
    if (!node) exit(OVERFLOW); //如果申请失败，退出
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

//遍历频度链表结点，判断字符是否在其中，如果在其中，频度增加，如果不在其中，创造新节点
void GetFre(char*a,ListNode* head){    //遍历字符串输入，改变频度
    int i=0;
    while(a[i]!='\0'){   //遍历链表 调整频度
        Search(a[i++],head);
    }//end:while
}//end:GetFre
//遍历字符串输入，改变频度的时候，只需要遍历字符串，调整频度即可
void Display(ListNode *node){   //展示频度
    int all=0;
    while(node!=NULL){
        if(node->c=='\0') {
            node=node->next;
            continue; //排除头节点
        }
        if(node->c=='\n'){printf("\'\\n\' %d %s\n",node->frequency,node->code);}
        else {printf("\'%c\' %d %s\n",node->c,node->frequency,node->code);}
        all+=node->frequency;
        node=node->next;
    }//end:while
    printf("%d\n",all);
}//end:Display
//展示频度的时候，只需要遍历链表，输出频度即可

void ReverseDisplay(ListNode*node){
    if(node==NULL) return;
    if(node->c=='\0') {
        ReverseDisplay(node->next);
        return;
    }
    if(node->c=='\n'){
        ReverseDisplay(node->next);
        printf("\'\\n\' %d %s\n",node->frequency,node->code);
        return;
    }
    else {
        ReverseDisplay(node->next);
        printf("\'%c\' %d %s\n",node->c,node->frequency,node->code);}//end:else
    return;
}//end:ReverseDisplay

void Sort(ListNode*head) {  //排序    **对排序规则稍加修改，按照从小到大的顺序进行，便于建树**
    ListNode *first = head->next; //从头节点下一个开始
    ListNode *node = head->next; //从头节点下一个开始
    int TemFrequency;
    char TemChar;
    while (first) {
        while (node->next) {
            if (node->next->frequency > node->frequency) {  //交换数据域
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

void ReverseList(ListNode*head){  //反转链表
    ListNode *node=head->next;
    ListNode *tem;
    head->next=NULL;
    while(node){
        tem=node->next;
        node->next=head->next;
        head->next=node;
        node=tem;
    }
}//end:ReverseList

int HasNoParents(ListNode*head){  //判断是否有父母结点
    head=head->next;   //跳过头节点
    while (head->next!=NULL) {  //遍历链表，判断是否有父母结点
        if(head->parent==NULL) return 1;
        head=head->next;
    }
}//end:HasParents

ListNode* InsertNode(ListNode*LC,ListNode*RC,ListNode*head){  //按照频度顺序插入结点
    int fre=LC->frequency+RC->frequency;
    while(head->next->frequency<=fre) {
        head=head->next; //由于整个链表是按照顺序排列，只需在下一个结点的频度大于此节点的频度时插入即可
        if(head->next==NULL) break;  //如果此时已经到达链表末尾，直接插入
    }
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
        ListNode*par=InsertNode(LChild,RChild,head);//插入节点
        RChild->parent=par;
        LChild->parent=par;

    }
}//end:CreateTree     //在此时，树中只有两个没有父母节点的节点，即为根节点与头节点

ListNode *GetRoot(ListNode*head){//获取哈夫曼树的根节点
    head=head->next;   //跳过头节点
    while(head){
        if(head->parent==NULL) return head;//找到没有父母结点的节点，即为根节点
        head=head->next;
    }
}//end:GetRoot


void GetHuffmanCode(ListNode* root, char* code, int depth) { //获取哈夫曼编码
    if (root->left == NULL && root->right == NULL) {
        root->code = (char*)malloc((depth + 1) * sizeof(char));
        strcpy(root->code, code);
        return;
    }
//如果左右子树都为空，说明是叶子节点，将编码存入code数组
    code[depth] = '0';
    code[depth + 1] = '\0';
    GetHuffmanCode(root->left, code, depth + 1);

    code[depth] = '1';
    code[depth + 1] = '\0';
    GetHuffmanCode(root->right, code, depth + 1);
}//end:GetHuffmanCode

void getWPL(ListNode* root, int depth, int* WPL) {//计算WPL
    if (root->left == NULL && root->right == NULL) {
        *WPL += depth * root->frequency;
        return;
    }//如果左右子树都为空，说明是叶子节点，将叶子节点的频度乘以深度
    getWPL(root->left, depth + 1, WPL);
    getWPL(root->right, depth + 1, WPL);
}//end:getWPL
//计算WPL的时候，只需要将叶子节点的频度乘以深度即可

void Encode(ListNode* head,char c, char* code){ //编码
    head=head->next;
    while(head){
        if(head->c==c){
            int i=0,j=0;
            while(code[j]!='\0'){//找到字符对应的编码
                j++;
            }
            while(head->code[i]!='\0'){//将编码存入code数组
                code[j++]=head->code[i++]; //将编码存入code数组
            }
            code[j]='\0';
            return;
        }
        head=head->next;
    }
}//end:Encode
//编码的时候，只需要找到对应的字符，将编码存入code数组即可

void UnCode(ListNode* head,char* code){ //解码
    head=head->next;
    ListNode *tem=head;
    int i=0;
    while(code[i]!='\0'){
        while(head){
            if(head->code!=NULL){//如果编码不为空
                int j=0;//比较编码与code数组
                while(head->code[j]!='\0'){//比较编码与code数组
                    if(head->code[j]!=code[i+j]) break;//比较编码与code数组
                    j++;
                }
                if(head->code[j]=='\0'){
                 printf("%c",head->c); //找到编码对应的字符
                    i+=j;
                    break;
                }
            }
            head=head->next;
        }
        head=tem;
    }
}//end:UnCode

void FreeList(ListNode*head){  //释放链表
    ListNode*tem;
    while(head){
        tem=head->next;
        free(head);
        head=tem;
    }
}//end:FreeList

int main() {
    ListNode *head = NULL;  //初始化头节点
    head = InitList();
    char code[500];     //初始化编码数组
    int WPL = 0;
    code[0] = '\0';
    char str[500];      //初始化字符串数组
    char tem;
    int i = 0;


    while ((tem = getchar()) != EOF) {
          str[i++] = tem; //输入字符串
    }
  str[i]='\0';


    GetFre(str, head);//获取频度
    Sort(head);  //排序
    ReverseList(head);//反转链表
    CreateTree(head);//创建树
    GetHuffmanCode(GetRoot(head), code, 0);//获取编码
    i=0;
    code[0]='\0';  //复用code数组
    while(str[i]!='\0'){
        Encode(head,str[i++],code);//编码
    }
    for(i=0;code[i]!='\0';i++){
        printf("%c",code[i]);//输出编码
    }
    printf("\n");
    UnCode(head,code);//解码
    getWPL(GetRoot(head), 0, &WPL);//计算WPL
    printf("\n%d\n",WPL);
    FreeList(head);//释放链表
    return 0;
}
//Your code end.