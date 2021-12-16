#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Info
{
    char* info1;
    char* info2;
    struct Info* next;
} Info;

typedef struct Node
{
    int key;
    int level;
    Info* info;
    struct Node* right; // указатель на левое поддерево
    struct Node* left; // указатель на правое поддерево
    struct Node* parent; // указатель на родителя
    struct Node* next;
} Node;

int Add(Node**);
int AddFromFile(Node**);
int FindByKey(Node**);
int FindMaxKey(Node**);
int Delete(Node**);
int Print(Node**);
int PrintTree(Node**);
int Timing(Node**);
int ABCD(Node**);
int Graphviz(Node**);

int getKey(int*);
int getKeyForPrint(char** str);
int getInt(int* f);
int getInfo(char** str);
void PrintNode(Node* elem, int ind);
int ShowNode(Node* elem, int level);
int find(Node* tmp, int key, int ind);
Node *findMaxNode(Node*);
Node* findMinNode(Node*);
Node *getNodeByKey(Node *root, int value);
Node* getNodeForPrint(Node *root, int value);
Node* CreateNode(Node *parent, int value, Info info, int lvl);
int insert(Node **head, int value);
void deleteTree(Node **root);
int removeNodeByPtr(Node *target, Node** head);
int fGetStr(FILE *file, char **str);
int PreOrderTravers(Node* head);
//int getInfoForFile(char** str, char* dop);
int dialog(const char *comands[], int N);
int Nodes(Node* nptr, FILE* file);
int Ways(Node* nptr, FILE* file);

const char* comands[] = {"0.Quit", "1.Add", "2.Add From File", "3.Find By Key", "4.Find Maximum Key", "5.Delete", "6.Print", "7.Print Tree", "8.Timing", "9.Travers", "10.Graphviz"};
const char *error_message[] = {"Done", "This element doesn't exist.", "Tree is empty.", "Error, check input data", "File is empty"};
const int SizeComands = sizeof(comands) / sizeof(comands[0]);
int (*fptr[])(Node**) = {NULL, Add, AddFromFile, FindByKey, FindMaxKey, Delete, Print, PrintTree, Timing, ABCD, Graphviz};

int main()
{
    Node* root = NULL;
    int rc = 0, f;
    while(rc = dialog(comands, SizeComands))
    {
        f = fptr[rc](&root);
        if(f == 1)
        {
            continue;
        }
    }
    deleteTree(&root);
    printf("Thank you, good luck! \n");
    return 0;
}

int Print(Node** head)
{
    int ind1, ind2 = 3;
    char* dopKey = (char*) malloc(1);
    ind1 = getKeyForPrint(&(dopKey));
    if(ind1 == 0)
    {
        ind2 = 2;
        Node* minelem = findMinNode(*head);
        if(minelem == NULL)
        {
            PrintNode(minelem, ind2);
        }
        while(minelem != NULL)
        {
            PrintNode(minelem, ind2);
            minelem = minelem->next;
        }
        return 1;
    }
    int key1 = atoi(dopKey);
    Node* minelem = getNodeForPrint(*head, key1);
    if(minelem == NULL)
    {
        PrintNode(minelem, ind2);
        return 1;
    }
    while(minelem != NULL)
    {
        PrintNode(minelem, ind2);
        minelem = minelem->next;
    }
    return 1;
}

void PrintNode(Node* elem, int ind)
{
    if(elem == NULL && ind == 3)
    {
        printf("%s\n", error_message[3]);
    }
    else if(elem == NULL && ind == 2)
    {
        printf("%s\n", error_message[2]);
    }
    else if(elem == NULL && ind == 1)
    {
        printf("%s\n", error_message[1]);
    }
    else
    {
        Info* p;
        p = elem->info;
        do
        {
            printf("Key: %d Info1: %s Info2: %s -> ", elem->key, p->info1, p->info2);
            p = p->next;
        } while(p != NULL);
    }
}
int ABCD(Node** head)
{
    PreOrderTravers(*head);
}
int PreOrderTravers(Node* head)
{
    if(head)
    {
        printf("%d ", head->key);
        PreOrderTravers(head->left);
        PreOrderTravers(head->right);
    }
}

int PrintTree(Node** head)
{
    if (*head == NULL) 
    {
        printf("%s\n", error_message[2]);
        return 1;
    }
    ShowNode(*head, 0);
    return 1;
}

int ShowNode(Node* elem, int level) 
{
    if(elem)
    {
        ShowNode(elem->left, level + 1);
        for(int i = 0; i < level; ++i)
        {
            printf("\t\t");
        }
        printf("%d", elem->key);
        printf("\n");
        ShowNode(elem->right, level + 1);
    }
    return 1;
}

Node* CreateNode(Node *parent, int value, Info elem, int lvl)
{
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->key = value;
    tmp->level = lvl;
    tmp->parent = parent;
    tmp->next = NULL;
    tmp->info = (Info*)malloc(sizeof(Info));
    *(tmp->info) = elem;
    return tmp;
}

int Add(Node **head) 
{
    Node *tmp = NULL;
    Node* dop = NULL;
    int key;
    int ind = 0, level = 0;
    Info* elem = (Info*)malloc(sizeof(Info));
    elem->info1 = (char*) malloc(1);
    elem->info2 = (char*) malloc(1);
    elem->next = NULL;
    getKey(&key);
    getInfo(&(elem->info1));
    getInfo(&(elem->info2));
    if (*head == NULL) 
    {
        *head = CreateNode(NULL, key, *elem, level);
        printf("%s\n", error_message[0]);
        return 1;
    }
    tmp = *head;
    while (tmp != NULL) 
    {

        if (key > tmp->key) 
        {
            level++;
            ind +=1;
            if (tmp->right != NULL) 
            {
                dop = tmp;
                tmp = tmp->right;
                continue;
            } 
            else 
            {
                dop = tmp;
                tmp->right = CreateNode(tmp, key, *elem, level);
                Node* ins;
                ins = dop->next;
                dop->next = tmp->right;
                tmp->right->next = ins;
                printf("%s\n", error_message[0]);
                return 1;
            }
        } 
        else if (key < tmp->key) 
        {
            level++;
            if (tmp->left != NULL) 
            {
                tmp = tmp->left;
                continue;
            } 
            else 
            {
                if(ind == 0)
                {
                    tmp->left = CreateNode(tmp, key, *elem, level);
                    tmp->left->next = tmp;
                    printf("%s\n", error_message[0]);
                    return 1;
                }
                else
                {
                    Node* ins;
                    tmp->left = CreateNode(tmp, key, *elem, level);
                    ins = dop->next;
                    dop->next = tmp->left;
                    tmp->left->next = ins;
                    printf("%s\n", error_message[0]);
                    return 1;
                }
            }
        } 
        else if (key == tmp->key) 
        {
            Info *p = (Info*)malloc(sizeof(Info));
            *p = *(tmp->info);
            tmp->info = elem;
            tmp->info->next = p;
            printf("%s\n", error_message[0]);
            return 1;
        }
    }
}

int AddFromFile(Node** head)
{
    Node* tmp = NULL;
    Node* dop = NULL;
    int key;
    int ind, level;
    FILE *file;
    file = fopen("C:/Program Files/Algorithms and data structures/4a1/tree.txt", "r");
    if(file == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    while(!feof(file))
    {
        level = 0;
        ind = 0;
        Info* elem = (Info*)malloc(sizeof(Info));
        elem->next = NULL;
        char* dopKey = (char*) malloc(127);
        elem->info1 = (char*) malloc(127);
        elem->info2 = (char*) malloc(127);
        if(fGetStr(file, &dopKey) == 1)
        {
            return 1;
        }
        if(fGetStr(file, &elem->info1) == 1)
        {
            return 1;
        }
        if(fGetStr(file, &elem->info2) == 1)
        {
            return 1;
        }
        key = atoi(dopKey);
        if (*head == NULL) 
        {
            *head = CreateNode(NULL, key, *elem, level);
            free(dopKey);
            continue;
        }
        tmp = *head;
        while (tmp != NULL) 
        {

            if (key > tmp->key) 
            {
                level++;
                ind +=1;
                if (tmp->right != NULL) 
                {
                    dop = tmp;
                    tmp = tmp->right;
                    continue;
                } 
                else 
                {
                    dop = tmp;
                    tmp->right = CreateNode(tmp, key, *elem, level);
                    Node* ins;
                    ins = dop->next;
                    dop->next = tmp->right;
                    tmp->right->next = ins;
                    break;
                }
            } 
            else if (key < tmp->key) 
            {
                level++;
                if (tmp->left != NULL) 
                {
                    tmp = tmp->left;
                    continue;
                } 
                else 
                {
                    if(ind == 0)
                    {
                        tmp->left = CreateNode(tmp, key, *elem, level);
                        tmp->left->next = tmp;
                        break;
                    }
                    else
                    {
                        Node* ins;
                        tmp->left = CreateNode(tmp, key, *elem, level);
                        ins = dop->next;
                        dop->next = tmp->left;
                        tmp->left->next = ins;
                        break;
                    }
                }
            } 
            else if (key == tmp->key) 
            {
                Info *p = (Info*)malloc(sizeof(Info));
                *p = *(tmp->info);
                tmp->info = elem;
                tmp->info->next = p;
                break;
            }
        }
        free(dopKey);
    }
    fclose(file);
    printf("%s\n", error_message[0]);
    return 1;
}

int Graphviz(Node** head)
{
    FILE* file;
    file = fopen("file.txt", "w+");
 
    fprintf(file, "digraph G{\nnode [shape = record];\n");
    Nodes(*head, file);
    Ways(*head, file);
    fprintf(file, "}");

    fclose(file);
    system("dot \"file.txt\" | neato -n -Tpng -o \"tree\".png");
    return 1;
}

int Nodes(Node* nptr, FILE* file) 
{
    if (nptr == NULL)
        return 0;
    if (nptr != NULL) 
    {
        Info* tmpinfo = nptr->info;
        fprintf(file, "node%d[shape = record, label = \" {< key > %d | { < info > %s %s", nptr->key, nptr->key, tmpinfo->info1, tmpinfo->info2);
        for (tmpinfo = tmpinfo->next; tmpinfo; tmpinfo = tmpinfo->next)
            fprintf(file, "\\n%s %s", tmpinfo->info1, tmpinfo->info2);
        fprintf(file, "}}\"];\n");
        Nodes(nptr->left, file);
        Nodes(nptr->right, file);
        return 0;
    }
    return 0;
}
 
int Ways(Node* nptr, FILE* file) 
{
    if (nptr == NULL)
        return 0;
    if (nptr != NULL) 
    {
        Info* tmpinfo = nptr->info;
        if (nptr->left)
            fprintf(file, "\"node%d\":info -> \"node%d\":key;\n", nptr->key, nptr->left->key);
        if (nptr->right)
            fprintf(file, "\"node%d\":info -> \"node%d\":key;\n", nptr->key, nptr->right->key);
        // "node0":f2 -> "node4":f1;
        Ways(nptr->left, file);
        Ways(nptr->right, file);
        return 0;
    }
    return 0;
}

int FindMaxKey(Node **head) 
{
    Node *tmp = NULL;
    tmp = *head;
    int ind = 1;
    while (tmp->right != NULL) 
    {
        tmp = tmp->right;
    }
    PrintNode(tmp, ind);
    return 1;
}

int FindByKey(Node** head)
{
    Node *tmp = NULL;
    int key, ind = 1;
    getKey(&key);
    if(find(*head, key, ind) == 0)
    {
        PrintNode(tmp, ind);
    }
    return 1;
}

int find(Node* tmp, int key, int ind)
{
    while (tmp != NULL) 
    {
        if (key < tmp->key) 
        {
            tmp = tmp->left;
            continue;
        } 
        else if (key > tmp->key) 
        {
            tmp = tmp->right;
            continue;
        } 
        else if(key == tmp->key)
        {
            if(ind == 1)
            {
                PrintNode(tmp, ind);
            }
            return 1;
        }
    }
    return 0;
}

int insert(Node **head, int k) 
{
    Node *tmp = NULL;
    int level = 0;
    Info* elem = (Info*)malloc(sizeof(Info));
    elem->info1 = (char*) malloc(1);
    elem->info2 = (char*) malloc(1);
    *(elem->info1) = 'a';
    *(elem->info2) = 'a';
    elem->next = NULL;
    if (*head == NULL) 
    {
        *head = CreateNode(NULL, k, *elem, level);
        return 1;
    }
    tmp = *head;
    while (tmp) 
    {
        if (k > tmp->key) 
        {
            if (tmp->right) 
            {
                tmp = tmp->right;
                continue;
            } else 
            {
                tmp->right = CreateNode(tmp, k, *elem, level);
                return 1;
            }
        } 
        else if (k < tmp->key) 
        {
            if (tmp->left) 
            {
                tmp = tmp->left;
                continue;
            } else 
            {
                tmp->left = CreateNode(tmp, k, *elem, level);
                return 1;
            }
        } 
        else if (k == tmp->key) 
        {
            Info *p = (Info*)malloc(sizeof(Info));
            *p = *(tmp->info);
            tmp->info = elem;
            tmp->info->next = p;
            return 1;
        }
    }
}

int Timing(Node** head)
{
    FILE* file;
    file = fopen("timing1.txt", "w + t");
    if(file == NULL)
    {
        return 1;
    }
    Node* root = NULL;
    int n = 100, key[10000], k, cnt = 1000000, i, m, ind = 0;
    clock_t first, last;
    srand(time(NULL));
    while(n-- > 0)
    {
        for(i = 0; i < 10000; ++i)
        {
            key[i] = rand() * rand();
        }
        for(i = 0; i < cnt; )
        {
            k = rand() * rand();
            if (insert(&root, k))
            {
                ++i;
            }
        }
        m = 0;
        first = clock();
        for(i = 0; i < 10000; ++i)
        {
            if(find(root, key[i], ind))
            {
                ++m;
            }
        }
        last = clock();
        printf("%d items was found\n", m);
        printf("test #%d, number of nodes = %d, time = %d\n", 100 - n, (100 - n)*cnt, last - first);
        fprintf(file, "%d   %d\n", (100 - n)*cnt, last - first);
    }
    deleteTree(&root);
    fclose(file);
    return 1;
}

int Delete(Node** head)
{
    int key, ind;
    getKey(&key);
    Node* target = getNodeByKey(*head, key);
    ind = removeNodeByPtr(target, &(*head));
    if(ind == 1)
    {
        *head = NULL;
    }
    return 1;
}

int removeNodeByPtr(Node *target, Node** head) 
{
    if(target == NULL)
    {
        printf("%s\n", error_message[1]);
    }
    else if (target->left && target->right) 
    {
        Node *localMax = (Node*) malloc(sizeof(Node));
        localMax = findMaxNode(target->left);
        target->key = localMax->key;
        *(target->info) = *(localMax->info);
        if(target->parent == NULL)
        {
            removeNodeByPtr(localMax, &(*head));
        }
        else if(target == target->parent->right)
        {
            target->parent->next = localMax->next;
            removeNodeByPtr(localMax, &(*head));
        }
        else
        {
            removeNodeByPtr(localMax, &(*head));
        }
    } 
    else if (target->left != NULL) 
    {
        if (target->parent == NULL)
        {
            if(target->left->right != NULL)
            {
                Node* dop;
                dop = target->left->right;
                while(dop->right != NULL)
                {
                    dop = dop->right;
                }
                dop->next = target->next;
            }
            else
            {
                target->left->next = target->next;
            }
            target->left->parent = target->parent;
            *head = target->left;
            free(target);
        }
        else if (target == target->parent->left) 
        {
            if(target->left->right != NULL)
            {
                Node* dop;
                dop = target->left->right;
                while(dop->right != NULL)
                {
                    dop = dop->right;
                }
                dop->next = target->next;
            }
            else
            {
                target->left->next = target->next;
            }
            target->left->level -= 1;
            target->left->parent = target->parent;
            target->parent->left = target->left;
            free(target);
        } 
        else 
        {
            if(target->left->right != NULL)
            {
                Node* dop;
                dop = target->left->right;
                while(dop->right != NULL)
                {
                    dop = dop->right;
                }
                dop->next = target->next;
            }
            else
            {
                target->left->next = target->next;
            }
            target->left->level -= 1;
            target->left->parent = target->parent;
            target->parent->right = target->left;
            free(target);
        }
    } 
    else if (target->right != NULL) 
    {
        if(target->parent == NULL)
        {
            *head = target->right;
            (*head)->parent = NULL;
            free(target);
        }
        else if (target == target->parent->right) 
        {
            target->right->level -= 1;
            target->parent->next = target->next;
            target->parent->right = target->right;
            target->right->parent = target->parent;
            free(target);
        } 
        else 
        {
            Node* dop = target;
            while(dop != NULL && dop != dop->parent->right)
            {
                dop = dop->parent;
                if(dop->parent == NULL)
                {
                    dop = dop->parent;
                    break;
                }
            }
            if(dop != NULL)
            {
                dop->parent->next = target->next;
            }
            target->right->level -= 1;
            target->parent->left = target->right;
            target->right->parent = target->parent;
            free(target);
        }
    } 
    else 
    {
        if(target->parent == NULL)
        {
            free(target);
            printf("%s\n", error_message[0]);
            return 1;
        }
        else if (target == target->parent->left) 
        {
            Node* dop = target;
            while(dop != NULL && dop != dop->parent->right)
            {
                dop = dop->parent;
                if(dop->parent == NULL)
                {
                    dop = dop->parent;
                    break;
                }
            }
            if(dop != NULL)
            {
                dop->parent->next = target->next;
            }
            target->parent->left = NULL;
            free(target);
        } 
        else 
        {
            target->parent->next = target->next;
            target->parent->right = NULL;
            free(target);
        }
    }
    printf("%s\n", error_message[0]);
    return 0;
}

Node* findMaxNode(Node* elem)
{
    if(elem == NULL)
    {
        return elem;
    }
    while(elem->right != NULL)
    {
        elem = elem->right;
    }
    return elem;
}

Node* findMinNode(Node *elem) 
{
    if(elem == NULL)
    {
        return elem;
    }
    while (elem->left != NULL) 
    {
        elem = elem->left;
    }
    return elem;
}

Node *getNodeByKey(Node *root, int value) 
{
    while (root != NULL) 
    {
        if (root->key > value) 
        {
            root = root->left;
            continue;
        } else if (root->key < value) 
        {
            root = root->right;
            continue;
        } 
        else if (root->key == value)
        {
            return root;
        }
    }
    return NULL;
}

Node* getNodeForPrint(Node *root, int value)
{
    Node* elem;
    elem = findMinNode(root);
    if(elem == NULL)
    {
        return NULL;
    }
    while(elem->key <= value)
    {
        elem = elem->next;
        if(elem->next == NULL)
        {
            return NULL;
        }
    }
    return elem;
}

void deleteTree(Node **root) 
{
    if (*root) 
    {
        deleteTree(&((*root)->left));
        deleteTree(&((*root)->right));
        free(*root);
    }
}

int dialog(const char* comands[], int N)
{
    char* err = "";
    int rc;
    int i, n;

    do
    {
        puts(err);
        err = "Error! Repeat, please \n";
        for (i = 0; i < N; ++i)
        {
            puts(comands[i]);
        }
        puts("Make your choice!");
        n = getInt(&rc);
        if (n == 0)
        {
            rc = 0;
        }
    } while (rc < 0 || rc >= N);

    return rc;
}

int getKey(int* f)
{
    printf("Enter tne key: \n");
    int g; // помещаем результат работы scanf в эту переменную
    do
    {
            g = scanf("%d", f);
            if (g <= 0) 
            {
                printf("Error, wrong symbol \n");
                scanf("%*[^\n]"); // очищаем буфер scanf
            }
    } while (g <= 0);
    scanf("%*[^\n]");
    
     return g < 0 ? 0 : 1;
}

int getKeyForPrint(char** str)
{
    printf("Enter the key, please: \n");
    int n, m = 1;
     *str[0] = '\0';
    char buf[81];
    scanf("%*c");
    do {
        n = scanf("%80[^\n]", buf);
        if (n > 0) 
        {
        m += strlen(buf);
        *str = (char*)realloc(*str, m);
        strcat(*str, buf);
        return 1;
        }
        else if(n == 0)
        {
            return 0;
        }
    } while (n > 0);
    //scanf("%*c");
}

int getInfo(char** str)
{
  printf("Enter the information, please: \n");
  int n, m = 1;
  *str[0] = '\0';
  char buf[81];
  scanf("%*c");
  do {
    n = scanf("%80[^\n]", buf);
    if (n > 0) 
    {
      m += strlen(buf);
      *str = (char*)realloc(*str, m);
      strcat(*str, buf);
    }
  } while (n > 0);
  //scanf("%*c");
  return 1;
}

int fGetStr(FILE *file, char **str) 
{
    *str = (char *) malloc(sizeof(char));
    **str = '\0';
    int indic;
    char buf[81];
    size_t sizeOfStr = 1;
    do {
        indic = fscanf(file, "%80[^\n]", buf);
        if (indic > 0) {
            sizeOfStr += strlen(buf);
            *str = (char *) realloc(*str, sizeOfStr * sizeof(char));
            strcat(*str, buf);
        }
        else if (indic == 0) {
            fscanf(file, "%*c");
        }
        else 
            return 1;
    } while (indic > 0);
    return 0;
}

int getInt(int* f)
{
    int g; // помещаем результат работы scanf в эту переменную
    do
    {
            g = scanf("%d", f);

            if (g <= 0) // если вводим букву
            {
                printf("Error, wrong symbol \n");
                scanf("%*[^\n]"); // очищаем буфер scanf
            }
    } while (g <= 0 );

    if (*f <= 0) // проверка на неотрицательность
    {
        while (*f < 0)
        {
                printf("Error, enter positive number \n");
                scanf("%*[^\n]");
                scanf("%d", f);
        }
    }
    scanf("%*[^\n]");
     return g < 0 ? 0 : 1;
}