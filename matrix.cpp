#include<iostream>

class matrix* helper;
int flajok;

class elem{
	
	public:
		int value;//хначение в текущей €чейке
		
		//коорджинаты €чейки
		int xp;
		int yp;
		
		//ссылка на след €чейку
		elem* next;
		
		//конструктор €чейки
		elem(){
			std::cerr<<"One element created"<<std::endl;
		}
		
		//деструктор €чейки
		~elem(){
			std::cerr<<"One element deleted"<<std::endl;
		}

};

class matrix{
private:
	elem* matr_fe;//ссылка на первый элемент матрицы (левыый верхний угол)
	int x;//размер матрицы в ширину
	int y;//размер матрицы в высоту

public:
	
	//конструктор создани€ матрицы в него поступают ее рамеры	
	matrix(int x, int y);//сделана
	
	//деструктор
	~matrix();//сделана
		
	//выводит на экран матрицу
	void print();
	
	void del_list();
	
	set(){//ready
			elem* cur = this->matr_fe;
			for(int i = 1; i <= this->y; ++i){
				for(int z = 1; z <= this->x; ++z){
					std::cout<<"Vvedite znachenye dlya sttoki "<<i<<" i pozicii "<<z<<std::endl;
					//std::cin>>cur->value;
					cur->value = i*z;
					cur = cur->next;
				}
			}
		}
	
	void create_0_list();

	matrix& operator=( matrix& right){
		
		matrix* r = &right;
		
		if(flajok != 0){
			r = helper;	
		}
		
		this->x = r->x;
        this->y = r->y;
		
		if(this->matr_fe != NULL){
			this->del_list();
		}	
		
		this->create_0_list();		
		
		
		this->copy_list(r);
				
		if(flajok != 0){
			delete helper;	
			flajok = 0;
		}
				
		return *this;
    }

	matrix& operator+ (const matrix& m2)const{//vrode sdelana
    	
	matrix res(this->x, this->y);

    elem* cur = res.matr_fe;
    elem* cur1 = this->matr_fe;
    elem* cur2 = m2.matr_fe;
	for(int i = 1; i <= this->y; ++i){
		for(int z = 1; z <= this->x; ++z){
			cur->value = cur1->value + cur2->value;
			cur1 = cur1->next;
			cur2 = cur2->next;
			cur = cur->next;
		}
	}
	//res.print();
	
	matrix* vygr = new matrix(this->x, this->y);
	
	*vygr = res;
	  
	helper = vygr;
	
	flajok = 1;
	return *helper;
	}
	
	matrix& operator- (const matrix& m2)const{//vrode sdelana
    	
	matrix res(this->x, this->y);

    elem* cur = res.matr_fe;
    elem* cur1 = this->matr_fe;
    elem* cur2 = m2.matr_fe;
	for(int i = 1; i <= this->y; ++i){
		for(int z = 1; z <= this->x; ++z){
			cur->value = cur1->value - cur2->value;
			cur1 = cur1->next;
			cur2 = cur2->next;
			cur = cur->next;
		}
	}
	//res.print();
		
	matrix* vygr = new matrix(this->x, this->y);
	
	*vygr = res;
	  
	helper = vygr;
	
	flajok = 1;
	return *helper;
	}
	
	matrix& operator* (const matrix& m2)const{//vrode sdelana
    	
	matrix res(m2.x, this->y);

    elem* cur = res.matr_fe;
    elem* cur1 = this->matr_fe;
    elem* cur2 = m2.matr_fe;
	for(int i = 1; i <= this->y; ++i){
		for(int z = 1; z <= this->x; ++z){
			
			for(int q = 1; q <= this->x; ++q){
				cur1 = this->matr_fe;
    			cur2 = m2.matr_fe;
				while(!((cur2->yp == q) && (cur2->xp == cur->xp))){
					cur2 = cur2->next;
				}
				while(!((cur2->xp == q) && (cur1->yp == cur->yp))){
					cur2 = cur2->next;
				}
				cur->value += (cur1->value)*(cur2->value);	
			}
			cur = cur->next;
		}
	}
	//res.print();
	
	matrix* vygr = new matrix(this->x, this->y);
	
	*vygr = res;
	  
	helper = vygr;
	
	flajok = 1;
	return *helper;
	}
	
	bool copy_list(matrix* istochnic);
};

//конструктор создани€ матрицы в него поступают ее рамеры	
matrix::matrix(int chir, int vys){//ready

this->x = chir;//сохран€ем размеры в класс матрицы
this->y = vys;//сохран€ем размеры в класс матрицы
this->matr_fe = NULL;

//создаем €чейки матрицы и заполн€ем их нул€ми;
this->create_0_list();

std::cerr<<"One matrix created"<<std::endl;		
};

matrix::~matrix(){

//вызываем функцию удалени€ списка из €чеек

del_list();

std::cerr<<"One matrix deleted"<<std::endl;

}

//выводит на экран матрицу
void matrix::print(){//ready
	elem* cur = this->matr_fe;
		for(int i = 1; i <= this->y; ++i){
			for(int z = 1; z <= this->x; ++z){
				if((cur->value < 10) && (cur->value >= 0)){
					std::cout<<cur->value<<"  ";
				}
				else{
					std::cout<<cur->value<<" ";
				}
				cur = cur->next;
			}
		puts(" ");
	}
}

//функци€ отладки, привлекает к месту на экрани, при помощи заполнени€ этого места большим количеством знаков !
void otlad(){
	for(int i = 0; i < 100; ++i){
		for(int z = 0; z < 100; ++z){
			std::cout<<"!";
		}
		std::cout<<""<<std::endl;
	}
}

void matrix::del_list(){
	
//создаем указатель на текущий ээлемент	
elem* cur = this->matr_fe;
		
while(this->matr_fe->next->next){

	while(cur->next->next){
		cur = cur->next;
	}

	delete cur->next;
	cur->next = NULL;
	cur = this->matr_fe;
}

delete this->matr_fe->next;
this->matr_fe->next = NULL;
delete this->matr_fe;
this->matr_fe = NULL;

}

bool matrix::copy_list(matrix* istochnic){
	
	if((this->x != istochnic->x) || (this->y != istochnic->y)){
		return false;
	}
		
	elem* cur_l = this->matr_fe;
	elem* cur_r = istochnic->matr_fe;
			
	for(int i = 1; i <= this->y; ++i){
		for(int z = 1; z <= this->x; ++z){
			cur_l->value = cur_r->value;	
			cur_r = cur_r->next;			
			cur_l = cur_l->next;
		}
	}
	
	return true;
}

void matrix::create_0_list(){
		//"положение курсора" (указывает с какой €чейком мы работаем в данный момент) изначально указывает на несуществующую €чейку (мнимую)

	if(!matr_fe){

	int flagY = 0;
	int flagX = 0;
		
	this->matr_fe = new elem;//создаем первую €чейку

	this->matr_fe->next = NULL;//на след пока указатель равен нулю

	//задаем координаты первой €чейки
	matr_fe->xp = 1;
	matr_fe->yp = 1;
	matr_fe->value = 0;
			
	//смещаем положение куурсосра  на текущюю €чейку		
	flagX++;	
	flagY++;

	//создаем указатель на текущуюю €€чейку, с которым будем потом работать
	elem* cur = this->matr_fe;	

	//в дангом цикле выделим в оперативе места под все €чейки матрицы и заполним их нул€ми
	while(1){
		//эта проверка нужнга, иначе матрица будет раст€нута на одну строку
		if(flagX < this->x){//
			
		cur->next = new elem;
		cur->next->value = 0;
		cur->next->next = NULL;
	
		flagX++;
		cur->next->xp = flagX;
		cur->next->yp = flagY;
		
		cur = cur->next;//перемещаем наш указатель на след €чейку
	}
	
	else{
	
		if(flagY < this->y){//если это верно, то пара перейти на новую строку
			cur->next = new elem;
			cur->next->value = 0;
			cur->next->next = NULL;
			flagY++;//вот он,  переход на новую строку
			flagX = 1;
			
			cur->xp = flagX;
			cur->yp = flagY;
			cur= cur->next;//перемещаем наш указатель на след €чейку
			}
				
			else{//в этом случае пам€ть под все €чейки вылделена и матрица заполнена нул€ми
				break;
			}	
		}
	}
	}
	
		else{
			elem* curr = this->matr_fe;
			while(curr){
				curr->value = 0;
				curr = curr->next;
			}
		}
	
	}

int main(){
	
	flajok = 0;
	
	matrix a(2,3);
	matrix b(3,2);
	
	a.print();
	b.print();
	
	
	a*b;
	
	helper->print();
}
