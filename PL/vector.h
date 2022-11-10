//vector的简单实现

#ifndef VECTOR_H
#define VECTOR_H

namespace mystl{

    template<class Object>
    class vector_
    {
        private:
            int theSize;
            int theCapacity;
            Object* Objects;
        public:
            explite vector_(int init = 0)
            {
                theSize=0;
                theCapacity=init+5;
                Objects = new Object[theCapacity];
            }

            ~vector_()
            {
                delete[] Objects;
            }

            //insert function
            void push_back(const Object x){
                *(Objects+theSize)=x;
                theSize++;
            }

            void pop_back(){
                theSize--;
            }

            void reserve(int newCapacity){
                if(newCapacity <= theSize){
                    return ;
                }
                Object* temp=Objects;
                theCapacity=newCapacity;
                Objects=new Object[theCapacity];
                for(int i=1;i<=theSize;i++){
                    Objects[i]=temp[i];
                }
                delete[] temp;
            }

            void resize(int newSize){
                if(newSize<theSize){
                    return;
                }

                reserve(newSize*2+1);
                theSize=newSize;
            }

            int size(){
                return theSize;
            }

            bool empty(){
                return !theSize;
            }
    };

}

#endif