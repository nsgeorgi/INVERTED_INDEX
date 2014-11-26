#include <cstdlib>
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <conio.h>

struct node
{
    int data;
    int height;
	node *left;
	node *right;
};
typedef struct node *nodeptr;


class Avl
{

    public:



        Avl();
        virtual ~Avl();
        void insert_node(int d,nodeptr &);
        void delete_node(int, nodeptr &ptr);
        int delete_more(nodeptr &p);
        int max(int value1, int value2);
        int height(nodeptr p);
        nodeptr  rotation_left(nodeptr &pp);
        nodeptr rotation_right( nodeptr &pp);
        nodeptr rotation_LR( nodeptr &pp);
        nodeptr rotation_RL( nodeptr &pp);
        void inorder(char a[],nodeptr &p);
};


class SortedArray
{
    public:
    int id;
    int plithos;
    Avl  avl;
    nodeptr pointer;
    SortedArray();
    virtual ~SortedArray();

};




Avl::Avl()
{

}

Avl::~Avl()
{
}

 void Avl::insert_node(int d, nodeptr &ptr)
 {

    if (ptr==NULL)
	{
		ptr = new node;
		ptr->data = d;
		ptr->height=0;
		ptr->left=NULL;
		ptr->right = NULL;
	}
	else
	{
		if (d<ptr->data)
		{
			insert_node(d,ptr->left);
			if ((height(ptr->left) - height(ptr->right))==2)
			{

                if (d<ptr->left->data)
			ptr=rotation_left(ptr);
			else
			ptr=rotation_RL(ptr);
			}
		}
        else if (d>ptr->data)
        {
            insert_node(d,ptr->right);
			if ((height(ptr->right) - height(ptr->left))==2)
			{
            if (d>ptr->right->data)
			ptr=rotation_right(ptr);
			else
			ptr=rotation_LR(ptr);
			}

        }

int m,n,c;
m=height(ptr->left);
n=height(ptr->right);
c=max(m,n);
ptr->height = d + 1;
 }

 }
  void Avl::delete_node(int d,nodeptr &ptr)
{
    nodeptr  tmp;
	if (ptr==NULL)
	{
		cout<<"data doesnt exist !"<<endl;
	}
	else if ( d > ptr->data)
	{
		delete_node(d,ptr->right);
	}
	else if (d < ptr->data)
	{
		delete_node(d,ptr->left);
	}
	else if (ptr->left == NULL)
	{
		tmp=ptr;
		free(tmp);
		ptr=ptr->right;
		cout<<"data deleted successfully\n"<<endl;
	}
	else if (ptr->right == NULL)
	{
		tmp=ptr;
		ptr=ptr->left;
		free(tmp);
		cout<<"data deleted successfully\n"<<endl;
	}
	else if ((ptr->left == NULL) && (ptr->right == NULL))
	{
		tmp=ptr;
		free(tmp);
		ptr=NULL;
		cout<<"data deleted successfully\n"<<endl;
	}
	else
	{
		ptr->data = delete_more(ptr->right);
	}



}


int Avl::delete_more(nodeptr &p)
{
	int c;

	if (p->left == NULL)
	{
		c=p->data;
		p=p->right;
		return c;
	}
	else
	{
		c=delete_more(p->left);
		return c;
	}

}
int Avl::max(int value1, int value2) //briskoume to megalutero apo ta upsi twn paidiwn
{
	if (value1 > value2)
	return value1;
	else
	return value2;
}
int Avl::height(nodeptr p) //epistrefei to upsos tou kombou//
{
	int h;
	if (p == NULL)
	{
		return -1;
	}
	else
	{
		h = p->height;
		return h;
	}
}


nodeptr  Avl::rotation_left(nodeptr &pp)
{
    nodeptr p1;
	p1 = pp->left;
	pp->left = p1->right;
	p1->right = pp;

	pp->height = max(height(pp->left),height(pp->right)) + 1;
	p1->height = max(height(p1->left),pp->height) + 1;

	return p1;

}

nodeptr Avl::rotation_right(nodeptr &pp)
{

    nodeptr p1;
	p1 = pp->right;
	pp->right = p1->left;
	p1->left = pp;
	pp->height = max(height(pp->left),height(pp->right)) + 1;
	p1->height = max(pp->height,height(p1->right)) + 1;

	return p1;
}


nodeptr Avl::rotation_RL(nodeptr &pp)
{
    pp->left=rotation_right(pp->left);
	return rotation_left(pp);
}

nodeptr Avl::rotation_LR(nodeptr &pp)
{
     pp->right=rotation_left(pp->right);
	return rotation_right(pp);

}

void Avl::inorder(char a[], nodeptr  &p)
{
    ofstream myfile3;
   myfile3.open(a,ios:: out| ios:: app);

    if (p!=NULL)
	{
		inorder(a,p->left);
		cout<<p->data<<"\t";
		myfile3<<p->data<<"\t";

		inorder(a,p->right);
	}

    myfile3.close();
}

 SortedArray::SortedArray()
{

    pointer==NULL;

}

SortedArray::~SortedArray()
{
    pointer=NULL;
}




void bubblesort(SortedArray array[],int n);




int main()
{


    string str;
    char a[256];
    fstream myfile;
    myfile.open("commands1.txt"); // Προσπαθούμε να ανοίξουμε το αρχείο "a.txt"
if (!myfile) // Αν το f πάρει τιμή false τότε το αρχείο δεν άνοιξε
{
cerr<<"Could not open file"<<endl;
}
else
cout<<"File opened succesfully"<<endl;
SortedArray *array; //DESMEUOYME 1^6 XWRO  GIA TA ANTIKEIMENA THS KLASIS SORTEDARRAY

array=new SortedArray[1000000];


getline(myfile,str,' ');

cout<<str<<endl;
myfile.getline(a,256);
fstream myfile1;
cout<<a<<endl;
myfile1.open(a);
if (!myfile1)
{
cerr<<"Could not open file"<<endl;
}
else
cout<<"File opened succesfully"<<endl;
int num;
bool flag;
int j=0;
int tmp;
for (int i=0; i<1000000; i++) //arxikopoioume ola ta id me -1
{
 array[i].id=-1;
  array[i].plithos=0;
}
for (int i=0; i<1000000; i++)
{
    j=0;
    flag=false;
    myfile1>>tmp;   //diavazei to id apo to arxeio


    while(array[j].id!=-1)
    {
        if (tmp==array[j].id) //ama uparxei to id ston pinaka tote diavasw to link tou
                                // kai to metaferw ekei pou idi uparxei to id
        {
            myfile1>>num;

        array[j].avl.insert_node(num,array[j].pointer);
        array[j].plithos++;
        flag=true;
        break;
        }

        j++;
    }
if (flag==true) continue;

array[j].id=tmp;       //an den uparxei to id ston pinaka tote to ekxwrw kai eisagw to link tou sto avl
myfile1>>num;

array[j].avl.insert_node(num,array[j].pointer);
array[j].plithos++;

}

//TAKSINOMISI PINAKA
int apo=0;
int n=1000000;
int eos=1000000;
bubblesort(array,n);




//ENTOLES EISAGWGIS  KAI DIAGRAFIS
int key;
int x;

getline(myfile,str,' ');
cout<<str<<endl;
bool found=false;

while(str.compare("WRITE_INDEX")!=0)
{

int n=1000000;
//EISAGWGI STOIXEIOU

if (str.compare("INSERT_LINK")==0)

{
myfile>>key;
for (int i=0; i<1000000; i++)
{
if (key==array[i].id)
{
    x=i;
found=true;
break;
}
else continue;
}
// ANAZITISI STOIXEIOU ID


if (found==false)
cout<<"key not found !"<<endl;
else
{

myfile>>num;

array[x].avl.insert_node(num,array[x].pointer);
array[x].plithos++;
}

}


//DIAGRAFI STOIXEIOU
else if (str.compare("DELETE_LINK")==0)
{
for (int i=0; i<1000000; i++)
{
if (key==array[i].id)
{
    x=i;
found=true;
break;
}
else continue;
}
// ANAZITISI STOIXEIOU ID


if (found==false) cout<<"key not found !"<<endl;
else
{

myfile>>num;
array[x].avl.delete_node(num,array[x].pointer);
array[x].plithos--;
}
}
myfile.getline(a,256);
getline(myfile,str,' ');
cout<<str<<endl;
}





myfile.getline(a,256);


ofstream myfile2;
//ME COUT STIN OTHONI MOU TA EMFANIZEI OLA SWSTA OTAN TA EMFANIZW STO ARXEIO OMWS TA EMFANIZEI ME FTHINOUSA SEIRA !
for (int i=0; i<1000000; i++)
{
    if(array[i].id==-1) continue;
    cout<<"ID"<<array[i].id<<"\t";
    cout<<"PLITHOS "<<array[i].plithos<<"\t >>";
    array[i].avl.inorder(a,array[i].pointer);
    cout<<endl;
    cout<<endl;
}

// EMFANISI STO ARXEIO
//TA EMFANIZEI ME FTHINOUSA SEIRA !

for (int i=0; i<1000000; i++)
{   myfile2.open(a, ios::out | ios::app);
    if(array[i].id==-1) continue;
    myfile2<<"ID"<<array[i].id<<"\t";
    myfile2<<"PLITHOS "<<array[i].plithos<<"\t >>";
    myfile2.close();
array[i].avl.inorder(a,array[i].pointer);
   myfile2.open(a, ios::out | ios::app);
   myfile2<<endl;
   myfile2.close();
}



myfile.close();
myfile1.close();

    return 0;
}


void bubblesort(SortedArray array[],int n)
{
    int i,k;
    SortedArray temp;
    for (i=1;i<n;i++)
    {
        for (k=n-1; k>=i; k--)
        {
            if (array[k].id<array[k-1].id)
            {
                temp=array[k];
                array[k]=array[k-1];
                array[k-1]=temp;

                }
            }
        }
    }

