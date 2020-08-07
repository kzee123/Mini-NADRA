#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include<string>
using namespace std;

static int id=1;

class nadra
{
	struct link
	{
		int CNIC; //( 4 digit number, different for everyone)
		string name;
		string FatherName;
		char gender;
		string address;//(address should be short, e.g. hayatabad Peshawar)
		link* next;
	};
    struct node
    {
        node* left;
        node* right;
        link* head;
		int u_id;

        int height;
    };
	
    node* root =NULL;

    node* insert(int nic, string nam, string fname, char g, string add, node* t)
    {
    	
        if(t == NULL)
        {
        	
            t = new node;
            
            t->head = new link;
            t->head->CNIC = nic;
            t->head->name = nam;
            t->head->FatherName = fname;
            t->head->gender = g;
            t->head->address = add;
            t->u_id = id;
            t->height = 0;
            t->left = t->right = NULL;
            id++;
        }
        else if(id < t->u_id)
        {
            t->left = insert(nic, nam,fname,g,add, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(id < t->left->u_id)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if( id > t->u_id)
        {
            t->right = insert(nic, nam,fname,g,add, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(id > t->right->u_id)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    node* singleRightRotate(node* t)
    {
        node* k = t->left;
        t->left = k->right;
        k->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        k->height = max(height(k->left), t->height)+1;
        return k;
    }

    node* singleLeftRotate(node* t)
    {
        node* k = t->right;
        t->right = k->left;
        k->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        k->height = max(height(t->right), t->height)+1 ;
        return k;
    }

    node* doubleLeftRotate(node* t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node* t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }
    node *  balance( node *t )
	{
		if( t == NULL)
		{}

		if( height( t->left ) - height( t->right ) > 1 )
		{
			if( height( t->left->left ) >= height( t->left->right ) )
				t=singleRightRotate( t );
			else
				t=doubleRightRotate( t );
		}
		else if( height( t->right ) - height( t->left ) > 1 )
		{
			if( height( t->right->right ) >= height( t->right->left))
			t=singleLeftRotate ( t );
			else
			t=doubleLeftRotate( t );
		}
		t->height = max( height( t->left ), height( t->right ) ) + 1;
		return t;
	}








    node* del(int nic, string nam,string fname,char g,string add, node* t)
    {
        node* temp;

        if(t == NULL)
            return NULL;

        else if(id < t->u_id)
            t->left = del( nic, nam,fname,g,add, t->left);
        else if(id > t->u_id)
            t->right = del(nic, nam,fname,g,add, t->right);
            
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->u_id = temp->u_id;
            //t->right = del(t->data, t->right);
            t->right = del(nic, nam,fname,g,add, t->right);
        }

        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t!=NULL)
	   t = balance( t );
	   return t;
	   
	   
        if(t == NULL)
            return t;
    }
	
	void update(int nic, string nam,string fname,char g,string add,int d, node* t)
	{
		if(t== NULL)
		{
			cout << "tree empty";
			return;
		}
			
		if(d == t->u_id)
		{
			t->head->CNIC = nic;
            t->head->name = nam;
            t->head->FatherName = fname;
            t->head->gender = g;
            t->head->address = add;
			return;
		}
		
		if(d < t->u_id)
		{
			 update(nic,nam,fname,g,add,d,t->left);
			 return;
		}
		if(d >t->u_id)
		{
			update(nic,nam,fname,g,add,d, t->right);
			return;
		}
	}
	
	void search(int d, node* t)
	{
		if(t== NULL)
		{
			cout << "Not found";
			return;
		}
		
		if(d == t->u_id)
		{
			cout  << "Person found..." << endl << "CNIC: " << t->head->CNIC << " " <<"Name: " << t->head->name << " " <<"Father's Name: " << t->head->FatherName << " " <<"Gender" << t->head->gender << " " <<"Address: " <<  t->head->address;
			return;
		}
		
		if(d < t->u_id)
		{
			 return search(d,t->left);
		}
		if(d >t->u_id)
		{
			return search(d, t->right);
		}
	}
	
    int height(node *t)
    {
    	if(t==NULL)
    	{
    		return 0;
		}
		return t->height;
    }

    int getBalance(node* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void preorder(node* t)
    {
        if(t == NULL)
            return;
        cout << "ID: " << t->u_id << "\t";
        cout << "CNIC: "<<t->head->CNIC << " ";
        cout << "\t" << "Name: "<<t->head->name << "\t ";
        cout << "Father Name:- "<<t->head->FatherName<< "\t Gender   " <<t->head->gender <<"\t Address:-    "<<t->head->address<<"     "<<endl<<endl;
		preorder(t->left);
        preorder(t->right);
    }

public:
    avltree()
    {
        root = NULL;
	}
	
    void insert(int nic, string nam, string fname, char g, string add)
    {
        root = insert(nic, nam,fname,g,add, root);
    }
    
    void search(int id)
    {
    	search(id,root);
	}
	
	void update(int nic, string nam, string fname, char g, string add, int d)
	{
		update(nic, nam,fname,g,add,d,root);
	}

    void del(int nic, string nam, string fname, char g, string add)
    {
        root = del(nic, nam,fname,g,add, root);
    }
//    void search(node *t)
//    {
//    	root = search(root);
//	}

    void display()
    {
        preorder(root);
        cout << endl;
    }
};

int main()
{
	nadra t;
	int u_id;
	string name;
	int CNIC;
	char gender;
	string Fname;
	string address;
	t.insert(1234, "paracha","shahaab",'M',"shahab@nu.edu.pk");
    t.insert(1325, "khan","ali",'M',"shouzab@nu.edu.pk");
    t.insert(4231, "mehmood","khan",'F',"asimmeh@nu.edu.pk");
	while(1)
	{
		system("cls");
		system("color 03");
		cout <<" #     #                        #     #    #    ######  ######     #    " << endl;
		cout <<" ##   ## # #    # #             ##    #   # #   #     # #     #   # #   " << endl;
		cout <<" # # # # # ##   # #             # #   #  #   #  #     # #     #  #   #  " << endl;
		cout <<" #  #  # # # #  # #             #  #  # #     # #     # ######  #     # " << endl;
		cout <<" #     # # #  # # #             #   # # ####### #     # #   #   ####### " << endl;
		cout <<" #     # # #   ## #             #    ## #     # #     # #    #  #     # " << endl;
	   	cout <<" #     # # #    # #             #     # #     # ######  #     # #     # " << endl;
		cout<<endl<<endl;
	   	
	   	cout<<"\n\t >**** Welcome ****<";
	    cout<<"\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] List all Contacts\n\t\t[3] Search for contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact\n\t\t[0] Exit\n\t\t=================\n\t\t";
	   	
	
	    
	   	char choice;
	   	choice = getch();
	   	
	   	if(choice == '1')
	   	{
	   		system("cls");
	   		cout << "Enter CNIC (4 digit unique number)";
	   		cin >> CNIC;
	   		cout << "Enter Name: ";
	   		cin >> name;
	   		cout << "Enter Father's Name: ";
	   		cin >> Fname;
	   		cout << "Enter Gender (M/F)";
	   		cin >> gender;
	   		cout << "Enter address: ";
	   		cin >> address;
	   		
	   		t.insert(CNIC, name, Fname, gender, address);
	   		cout << "Insertion successfull, Press any key to continue..,";
	   		getch();
		}
		
		else if(choice == '2')
		{
			system("cls");
			t.display();
			cout << endl << "Press any key to continue";
			getch();
		}
		
		else if(choice == '3')
		{
			system("cls");
			cout << "Enter your unique id: ";
			cin >>u_id;
			system("cls");
			
			t.search(u_id);
			cout << endl << "Press any key to continue...";
			getch();
		}
		
		else if(choice == '4')
		{
			system("cls");
			cout << "Enter Unique id: ";
			cin >> u_id;
			cout << "Enter CNIC (4 digit unique number)";
	   		cin >> CNIC;
	   		cout << "Enter Name: ";
	   		cin >> name;
	   		cout << "Enter Father's Name: ";
	   		cin >> Fname;
	   		cout << "Enter Gender (M/F)";
	   		cin >> gender;
	   		cout << "Enter address: ";
	   		cin >> address;
			
			t.update(CNIC,name,Fname,gender,address,u_id);
			cout << "Updated successfully...!";
			getch();
		}
		
		else if(choice == '5')
		{
			system("cls");
			cout << "Enter CNIC (4 digit unique number)";
	   		cin >> CNIC;
	   		cout << "Enter Name: ";
	   		cin >> name;
	   		cout << "Enter Father's Name: ";
	   		cin >> Fname;
	   		cout << "Enter Gender (M/F)";
	   		cin >> gender;
	   		cout << "Enter address: ";
	   		cin >> address;
			t.del(CNIC,name,Fname,gender,address);
			cout << "Deleted successfully...";
			getch();
		}
		else if(choice == '0')
		{
			break;
		}
		
	}
	
	
	
	    //system("cls");
	
}
