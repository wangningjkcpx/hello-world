#include <iostream>
#include <fstream>

using namespace std;

template<class T>
class Matrix;

// Forward declaration for friend functions
//Overloaded output operator
template<class T>
ostream & operator<<(ostream &os, Matrix<T> const &obj);

//Overloaded input operator
template<class T>
istream & operator>>(istream &is, Matrix<T> &obj);

//Overloaded multiplication operator,for multiplication calculation in the form scalar*matrix
template<class T>
Matrix<T> operator*(const T &lhs, const Matrix<T> &rhs);

//Overloaded division operator,for multiplication calculation in the form scalar/matrix
template<class T>
Matrix<T> operator/(const T &lhs, const Matrix<T> &rhs);

template<class T>
class Matrix{
	friend ostream & operator<< <>(ostream &os, Matrix<T> const &obj);
	friend istream & operator>> <>(istream &is, Matrix<T> &obj);
	friend Matrix<T> operator* <>(const T &lhs, const Matrix<T> &rhs);
	friend Matrix<T> operator/ <>(const T &lhs, const Matrix<T> &rhs);

public:
	Matrix();
	//Constructor function with given size of the matrix
	Matrix(int row, int col);
	//Synthesized copy constructor
	Matrix(const Matrix<T> &source);
	//Destructor function
	~Matrix();
	
	//Overloaded assignment operator
	Matrix<T> & operator=(const Matrix<T> &rhs);

	//Overloaded multiplication operator,for multiplication calculation in the form matrix*scalar
	Matrix<T> operator*(const T &rhs) const;
	Matrix<T> & operator*=(const T &rhs);

	//Overloaded multiplication operator,for multiplication calculation in the form matrix1*matrix2
	Matrix<T> operator*(const Matrix<T> &rhs) const;
	Matrix<T> & operator*=(const Matrix<T> &rhs);

	//Overloaded adding operator
	Matrix<T> operator+(const Matrix<T> &rhs) const;
	Matrix<T> & operator+=(const Matrix<T> &rhs);

	//Overloaded subtraction operator,for subtraction calculation in the form matrix1-matrix2
	Matrix<T> operator-(const Matrix<T> &rhs) const;
	Matrix<T> & operator-=(const Matrix<T> &rhs);

	//Overloaded subtraction operator,for subtraction calculation in the form -matrix
	Matrix<T> operator-() const;

	//Overloaded division operator,for division calculation in the form matrix1/matrix2
	Matrix<T> operator/(const Matrix<T> &rhs) const;
	Matrix<T> & operator/=(const Matrix<T> &rhs);

	//Overloaded division operator,for division calculation in the form matrix1/scalar
	Matrix<T> operator/(const T &rhs) const;
	Matrix<T> & operator/=(const T &rhs);

	//Calculation for determinant
	T detMatrix() const;
	//Calculation for inverse matrix
	Matrix<T> inverseMatrix() const;
	//Calculation for matrix transpose
	Matrix<T> transMatrix() const;

	//Elements initialization
	void Initelements();
	//Set matrix size
	void setSize(int row, int col);
	//Get row size
	int getRow() const;
	//Get col size
	int getCol() const;

private:
	int m_row; //Matrix row size 
	int m_col; //Matrix columns size
	T* m_data; //Matrix elements
};

template<class T>
Matrix<T>::Matrix():m_row(0) ,m_col(0) {
	m_data = NULL ; 
}

template<class T>
Matrix<T>::Matrix(int row , int col){
	if (row < 1 || col < 1){
		m_row = 0 ;
		m_col = 0 ;
		m_data = NULL;
		cout << "Invalid data"<<endl;
		return; 
	}
	m_row = row;
	m_col = col;
	m_data = new T[row*col];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &source){
	m_row = source.m_row;
	m_col = source.m_col;
	if ( source.m_data == NULL || source.m_row < 1 ||source.m_col < 1 )
		m_data = NULL;	
	else {
		m_data = new T[m_col * m_row];
		for (int i = 0; i<m_row*m_col; i++)
			m_data[i] = source.m_data[i];
	}	
}

template<class T>
Matrix<T>::~Matrix(){
	m_row = 0;
	m_col = 0;
	if (m_data != NULL)
		delete [] m_data;
}

template<class T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> &rhs){
	if (this!=&rhs){
		delete [] m_data;
		m_data = NULL;
		m_row = rhs.m_row;
		m_col = rhs.m_col;
		if (rhs.m_data != NULL){
			m_data = new T[m_row*m_col];
			for (int i = 0; i<rhs.m_row*rhs.m_col; i++)
				m_data[i] = rhs.m_data[i];
		}
	}
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const T &rhs) const{
	int row = m_row;
	int col = m_col;
	Matrix<T> result(row , col);
	if ( m_data ==	NULL || m_row < 1 || m_col < 1)
		return result;	
	for (int i = 0; i<m_row*m_col; i++)
		result.m_data[i] = rhs * m_data[i];
	return result;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &rhs) const{
	if ( m_col != rhs.m_row ){
		cout<<"Matrix size unmatched"<<endl;
		Matrix<T> temp;
		return temp;
	}
	
	if (m_data == NULL || m_row < 1 || m_col < 1 || rhs.m_data == NULL || rhs.m_row < 1 || rhs.m_col < 1)
	{
		cout<<"Empty Matrix"<<endl;
		Matrix<T> temp;
		return temp;
	}

	Matrix<T> result(m_row , rhs.m_col);
	for(int i = 0; i<m_row; i++)
		for (int j = 0; j<rhs.m_col; j++){
			result.m_data[i*rhs.m_col+j] = 0;
			for (int k = 0; k<m_col; k++)
				result.m_data[i*rhs.m_col+j] += m_data[i*m_col+k] * rhs.m_data[k*rhs.m_col + j];
		}
	return result;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &rhs) const{
	if ( m_col != rhs.m_col || m_row!=rhs.m_row ){
		cout<<"Matrix size unmatched"<<endl;
		Matrix<T> temp;
		return temp;
	}

	if (m_data == NULL || m_row < 1 || m_col < 1 || rhs.m_data == NULL || rhs.m_row < 1 || rhs.m_col < 1)
	{
		cout<<"Empty Matrix"<<endl;
		Matrix<T> temp;
		return temp;
	}
	Matrix<T> result(*this);
	for(int i = 0; i<m_row*m_col; i++)		
		result.m_data[i] += rhs.m_data[i];
	return result;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &rhs) const{
	if ( m_col != rhs.m_col || m_row!=rhs.m_row ){
		cout<<"Matrix size unmatched"<<endl;
		Matrix<T> temp;
		return temp;
	}

	if (m_data == NULL || m_row < 1 || m_col < 1 || rhs.m_data == NULL || rhs.m_row < 1 || rhs.m_col < 1)
	{
		cout<<"Empty Matrix"<<endl;
		Matrix<T> temp;
		return temp;
	}
	Matrix<T> result(*this);
	for(int i = 0; i<m_row*m_col; i++)		
		result.m_data[i] -= rhs.m_data[i];
	return result;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const{
	Matrix<T> result(*this);
	if (m_data == NULL || m_row < 1 || m_col < 1)	
		return result;
	for(int i = 0; i<m_row*m_col; i++)		
		result.m_data[i] = -m_data[i];
	return result;
}

template<class T>
Matrix<T> Matrix<T>::operator/(const Matrix<T> &rhs) const{
	if (m_data == NULL || m_row < 1 || m_col < 1 )
	{
		cout<<"Empty Matrix"<<endl;
		Matrix<T> temp;
		return temp;
	}
	if ( rhs.m_data == NULL || rhs.m_row < 1 || rhs.m_col < 1 ||rhs.m_row != rhs.m_col|| rhs.detMatrix() == 0)
	{
		cout<<"Invalid data"<<endl;
		Matrix<T> temp;
		return temp;
	}
	Matrix<T> m = rhs.inverseMatrix();
	return (*this)*m;
}

template<class T>
Matrix<T> Matrix<T>::operator/(const T &rhs) const{
	int row = m_row;
	int col = m_col;
	Matrix<T> result(row , col);
	if ( m_data ==	NULL || m_row < 1 || m_col < 1)
		return result;	
	for (int i = 0; i<m_row*m_col; i++)
		result.m_data[i] = m_data[i] / rhs;
	return result;
}

template<class T>
Matrix<T> & Matrix<T>::operator*=(const T &rhs){
	*this = (*this) * rhs;
	return *this;
}

template<class T>
Matrix<T> & Matrix<T>::operator*=(const Matrix<T> &rhs){
	*this = (*this) * rhs;
	return *this;
}

template<class T>
Matrix<T> & Matrix<T>::operator+=(const Matrix<T> &rhs){
	*this = (*this) + rhs;
	return *this;
}

template<class T>
Matrix<T> & Matrix<T>::operator-=(const Matrix<T> &rhs){
	*this = (*this) - rhs;
	return *this;
}

template<class T>
Matrix<T> & Matrix<T>::operator/=(const T &rhs){
	*this = (*this) / rhs;
	return *this;
}

template<class T>
Matrix<T> & Matrix<T>::operator/=(const Matrix<T> &rhs){
	*this = (*this) / rhs;
	return *this;
}

template<class T>
T Matrix<T>::detMatrix() const{
	if (m_row != m_col){
		cout<<"Matrix size unmatched"<<endl;
		return 0;
	}
	Matrix<T> M(*this);
	int m,n,s,t,k=1;
	T c,x,sn,f = 1;
	for (int i = 0,j=0;i<m_row&&j<m_row;i++,j++){
		if (M.m_data[i*m_col +j] == 0){
			for (m=i;M.m_data[m*m_col+j] == 0; m++);
			if (m==m_row){
				sn=0;
				return sn;
			}
			else
				for (n=j; n<m_row; n++)
				{
					c=M.m_data[i*m_col + n];
					M.m_data[i*m_col+n] = M.m_data[m*m_col + n];
					M.m_data[m*m_col+n] = c;
				}
			k*=(-1);
		}
		for (s = m_row-1;s>i;s--)
		{
			x = M.m_data[s*m_col + j ];
			for (t=j; t<m_row; t++)
				M.m_data[s*m_col +t] -= M.m_data[i*m_col+t]*(x/M.m_data[i*m_col + j ]);
		}
	}
	for (int i=0; i<m_row; i++)
		f*=M.m_data[i*m_col + i];
	sn = k*f;
	return sn;

}

template<class T>
Matrix<T> Matrix<T>::inverseMatrix() const{
	int count = 0;
	T var = 0;
	T var1;
	if (m_row != m_col){
		cout<<"Matrix size unmatched"<<endl;
		Matrix<T> temp;
		return temp;
	}
	if ( (var=detMatrix())==0 || m_data == NULL || m_row < 1 || m_col < 1){
		Matrix<T> temp;
		cout<<"Invalid data"<<endl;
		return temp;
	}
	Matrix<T> temp1(m_row ,m_col );
	Matrix<T> temp2(m_row-1 ,m_col-1);
	for (int i = 0; i<m_row; i++)
		for (int j = 0; j<m_col; j++){
			int l;
			if ( (i+j)%2 == 0 )
				l=1;
			else l=-1;
			for (int k = 0;k<(m_row-1)*(m_col-1); ){
				if (count/m_row == i || count%m_row == j){
					count++;
					continue;
				}
				temp2.m_data[k] = m_data[count];
				k++;
				count++;
			}
			count = 0;
			var1 = temp2.detMatrix()*l/var;
			temp1.m_data[j*m_row+i] = var1?var1:0;
		}
		return temp1;
}

template<class T>
Matrix<T> Matrix<T>::transMatrix() const{
	if (m_row < 1 || m_col<1 || m_data == NULL){
		Matrix<T> temp;
		cout<<"Empty Matrix"<<endl;
		return temp;
	}
	Matrix<T> m(m_col,m_row);
	for (int i = 0; i<m_col; i++)
		for (int j = 0; j<m_row; j++)
			m.m_data[i*m_row + j] = m_data[j*m_col + i];
	return m;
}

template<class T>
void Matrix<T>::Initelements(){
	if (m_data != NULL)
		for (int i = 0; i < m_row*m_col; i++)
			m_data[i] = T();
}

template<class T>
void Matrix<T>::setSize(int row, int col){
	if ( !(row==0&&col==0) ){
		cout << "Invalid data"<<endl;
		return;
	}
	delete [] m_data;
	m_data = NULL;
	if (row*col != 0){
		m_data = new T[row*col];
		for (int i = 0; i < row*col; i++)
			m_data[i] = T();
	}
	m_row = row; 
	m_col = col;
}

template<class T>
int Matrix<T>::getRow() const{
	return m_row;
}

template<class T>
int Matrix<T>::getCol() const{
	return m_col;
}

template<class T>
ostream & operator<<(ostream &os, Matrix<T> const &obj){
	if (obj.m_data != NULL){
		for (int i = 0; i<obj.m_row*obj.m_col; i++){
			if ( (i+1)%obj.m_col == 0 )
				os<<obj.m_data[i]<<endl;
			else os<<obj.m_data[i]<<" ";
		}
	}
	else os<<"Empty Matrix"<<endl;
	return os;
}

template<class T>
istream & operator>>(istream &is, Matrix<T> &obj){
	if (obj.m_data != NULL){
		for (int i = 0; i<obj.m_row*obj.m_col; i++)
		{
			is>>obj.m_data[i];
		}
	}
	return is;
}

template<class T>
Matrix<T> operator*(const T &lhs, const Matrix<T> &rhs){
	int row = rhs.getRow();
	int col = rhs.getCol();
	Matrix<T> result(row , col);
	if ( rhs.m_data ==	NULL || rhs.m_row < 1 || rhs.m_col < 1)
		return result;	
	for (int i = 0; i<rhs.m_row*rhs.m_col; i++)
		result.m_data[i] = lhs * rhs.m_data[i];
	return result;
}

template<class T>
Matrix<T> operator/(const T &lhs, const Matrix<T> &rhs){
	if ( rhs.m_data == NULL || rhs.m_row < 1 || rhs.m_col < 1 ||rhs.m_row != rhs.m_col|| rhs.detMatrix() == 0)
	{
		cout<<"Invalid data"<<endl;
		Matrix<T> temp;
		return temp;
	}
	Matrix<T> m = rhs.inverseMatrix();
	return lhs*m;
}
