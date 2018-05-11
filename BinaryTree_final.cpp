#include<iostream>
#include<stdio.h>
#include<stdlib.h>
  
// Интерфейс
class Container
{
public:
    // Виртуальные методы, будут реализованы далее 
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;
    // Это потом заменим на перегруженный оператор <<
    virtual void print() = 0;

    // Виртуальный деструктор
    virtual ~Container();
};

Container::~Container() {
	;
}

// Реализация интерфейса

class node{
	public:
    	int value;			
    	node* left;	
		node* right;
		
		node(){
			std::cerr<<"One node created"<<std::endl;
			this->left = NULL;
			this->right = NULL;
			this->value = -999;
		}
		~node(){
			std::cerr<<"One node deleted"<<std::endl;
		}
};

class SimpleList: public Container
{
	void insert_h(node* cur, int value);//gotova
	void find_h(node** cur, int* flag, int value);//ready
public:
    SimpleList();//gotov
    ~SimpleList();//ready
    void insert(int value);//ready
    bool exists(int value);//ready
    void remove(int value);
    void print_h(node* cur, int level);//gotova				
    void print(){//gotova
    	print_h(this->root, 0);	
	}
	void del_h(node* cur){//gotova
		if(cur->left != NULL){
			del_h(cur->left);
		}
		if(cur->right != NULL){
			del_h(cur->right);
		}
		delete cur;
	}

protected:
    node* create(int i);//ready
    node* find(int i);//ready

    node* root;//tak i est
};

SimpleList::SimpleList()//gotov
{
    this->root = NULL;
    std::cerr<<"Binary tree created"<<std::endl;
};

SimpleList::~SimpleList()//gotov
{
    node* cur_elem = this->root;
    if(cur_elem == NULL){
    	std::cerr<<"Binary tree delited"<<std::endl;
	}
	else{
		del_h(cur_elem);
    
    	std::cerr<<"Binary tree delited"<<std::endl;
	}
	
};

// Create new element, set its value to 'i', return pointer to new element
node* SimpleList::create(int value)//done
{
    // Allocate memmory
    node* elem = new node;
    // Set value
    elem->value = value;
    // There is no next element, so set next to NULL
    elem->left = NULL;
    elem->right = NULL;

    return elem;
}

// Insert element 'elem' into list 'root' (on the 1st position),
// calls 'create' under the hood
void SimpleList::insert(int value)
{
    if(this->root == NULL)
    {
		node* elem = this->create(value);
        this->root = elem;
    }
    
    else
    {
    	insert_h(this->root, value);
    }
}

void SimpleList::insert_h(node* cur, int value){//вставка
	
	
	if(cur->left != NULL){
		if(cur->right != NULL){
			if(value < cur->value){
				insert_h(cur->left, value);
			}
			else{
				insert_h(cur->right, value);
			}
		}
		else{
			if(value < cur->value){
				insert_h(cur->left, value);
			}
			else{
				node* nce = this->create(value);
        		cur->right = nce;
			}
		}
	}
	else{
		if(cur->right != NULL){
			if(value < cur->value){
				node* nce = this->create(value);
        		cur->left = nce;
			}
			else{
				insert_h(cur->right, value);
			}
		}
		else{
			if(value < cur->value){
				node* nce = this->create(value);
        		cur->left = nce;
			}
			else{
				node* nce = this->create(value);
        		cur->right = nce;
			}
		}
	}
}


void SimpleList::find_h(node** cur, int* flag, int value){
		if((*cur)){		
		if((*cur)->value == value){
			*flag = 1;
		}
		else{
			if(value < (*cur)->value){
				(*cur) = (*cur)->left;
				find_h(cur, flag, value);	
			}
			else{
				(*cur) = (*cur)->right;
				find_h(cur, flag, value);
			}
		}
	}
	}


bool SimpleList::exists(int value)
{
    node* cur_element = this->find(value);
    return cur_element != NULL;
}

node* SimpleList::find(int value)
{
    int flag = 0;
    node* cur = this->root;
    if(this->root == NULL){
    	return NULL;
	}
    find_h(&cur, &flag, value);
    
    if(flag == 0){
    	return NULL;	
	}
    else{
    	return cur;
	}
}

void SimpleList::remove(int value){
	
    node* elem = this->find(value);
	
	if(elem == NULL){
        return;
    }
    
    else if(this->root == elem){
		if((this->root->right)&&(this->root->left)){
				node* temp1 = elem;
				temp1 = temp1->right;
				if(temp1->left){
					while(temp1->left->left){
						temp1 = temp1->left;
					}
					node* temp2 = temp1->left;
					temp1->left = temp2->right;
					elem->value = temp2->value;
					delete temp2;
				}
				else{
					temp1->left = this->root->left;
					node* yu = this->root;
					this->root = temp1;
					delete yu;
				}	
		}
		else{
			if(this->root->left){
				node* ty = this->root;
				this->root = this->root->left;
				delete ty;
			}
			else{
				if(this->root->right){
				node* ty = this->root;
				this->root = this->root->right;
				delete ty;
				}
				else{
					std::cout<<"This tree has only one element, so we cann`t delete it!"<<std::endl;
				}
			}
		}
	}
	else{
		if((elem->right)&&(elem->left)){
				node* temp1 = elem->right;
				if(temp1->left){
					while(temp1->left->left){
						temp1 = temp1->left;
					}
					node* temp2 = temp1->left;
					temp1->left = temp2->right;
					elem->value = temp2->value;
					delete temp2;
				}
				else{
					temp1->left = elem->left;
					int flag1 = 0;
					node* cur1 = this->root;
					while(flag1 == 0){
						if(value < cur1->value){
							if(cur1->left == elem){
								flag1 = 1;	
							}
							else{
								cur1 = cur1->left;
							}
						}
						else{
							if(cur1->right == elem){
								flag1 = 2;	
							}
							else{
								cur1 = cur1->right;
							}
						}
					}
					if(flag1 == 1){
						cur1->left = temp1;
					}
					else if(flag1 = 2){
						cur1->right = temp1;
					}
					else{
						std::cout<<"Error"<<std::endl;	
				//предыдущий->на елем = elem->left;?? рреализовано
					}
					
					delete elem;
				}	
		}
		else{
			if(elem->left){
				int flag1 = 0;
				node* cur1 = this->root;
				while(flag1 == 0){
					if(value < cur1->value){
						if(cur1->left == elem){
							flag1 = 1;	
						}
						else{
							cur1 = cur1->left;
						}
					}
					else{
						if(cur1->right == elem){
							flag1 = 2;	
						}
						else{
							cur1 = cur1->right;
						}
					}
				}
				if(flag1 == 1){
					cur1->left = elem->left;
				}
				else if(flag1 = 2){
					cur1->right = elem->left;
				}
				else{
					std::cout<<"Error"<<std::endl;	
				}
				delete elem;
			}
			else{
				if(elem->right){
					int flag1 = 0;
				node* cur1 = this->root;
				while(flag1 == 0){
					if(value < cur1->value){
						if(cur1->left == elem){
							flag1 = 1;	
						}
						else{
							cur1 = cur1->left;
						}
					}
					else{
						if(cur1->right == elem){
							flag1 = 2;	
						}
						else{
							cur1 = cur1->right;
						}
					}
				}
				if(flag1 == 1){
					cur1->left = elem->right;
				}
				else if(flag1 = 2){
					cur1->right = elem->right;
				}
				else{
					std::cout<<"Error"<<std::endl;	
				}
				//предыдущий->на елем = elem->right;
				delete elem;
				}
				else{
					int flag1 = 0;
				node* cur1 = this->root;
				while(flag1 == 0){
					if(value < cur1->value){
						if(cur1->left == elem){
							flag1 = 1;	
						}
						else{
							cur1 = cur1->left;
						}
					}
					else{
						if(cur1->right == elem){
							flag1 = 2;	
						}
						else{
							cur1 = cur1->right;
						}
					}
				}
				if(flag1 == 1){
					cur1->left = NULL;
				}
				else if(flag1 = 2){
					cur1->right = NULL;
				}
				else{
					std::cout<<"Error"<<std::endl;	
				}
					//предыдущий на елем равно нулл
					delete elem;
				}
			}
		}
	}
}

void SimpleList::print_h(node* cur, int level){//рекурсивная распечатка с графическим представлением
		if(cur){
			print_h(cur->right , level+1);//вывод правого поддерева
			for(int i = 0; i<level; i++){
				std::cout<<"            ";
			} 	
			
			std::cout<<cur->value<<std::endl;
			
			//std::cout<<"tip: "<<cur->type<<" znachenie: "<<cur->value<<std::endl;

			print_h(cur->left , level+1);//вывод левого поддерева
		}
}

int main()
{
    Container* c = new SimpleList();

	
    for(int i = 1; i < 10; i++)
        c->insert(i*i);
	
	c->insert(12);
	c->insert(13);
	c->insert(11);
    printf("List after creation:\n");
    c->print();
	
    if(c->exists(25))
        std::cout << "Search for value 25: found" << std::endl;
	
    if(!c->exists(111))
        std::cout << "Search for value 111: not found" << std::endl;
	int abc = 16;
	
    c->remove(abc);
    std::cout << "Removing: " << abc << std::endl;
    std::cout << "List after deletion of the element:" << std::endl;
    c->print();
	
    delete c;
    return 0;
}
