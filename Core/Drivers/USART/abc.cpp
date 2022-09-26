#include "abc.hh"


abc::abc(/* args */)
{
    char st = 's';
    uint32_t arr[10] = {0};
    uint32_t temp1 = 0;
    bool temp2 = false;
    int temp3 = 9878;
    RCC->AHB1ENR |= 1 << 0;
    GPIOA->MODER |= 0X01 << 10;
    //GPIOA->ODR |= 1 << 5;
    for(uint8_t i = 0; i < 10; i++){
        temp3 = i;
        arr[i] = i;
        temp2 = !temp2;
        GPIOA->ODR ^= 1 << 5;
    } 
    temp1 = -1;
    st = 'n';
    fun(temp3);
}
abc::abc(int &a)
{
    
    uint32_t temp1 = 0;
    bool temp2 = false;
    int temp3 = 9878;
    fun(temp3);
    RCC->AHB1ENR |= 1 << 0;
    GPIOA->MODER |= 0X01 << 10;
    //GPIOA->ODR |= 1 << 5;
    for(uint8_t i = 0; i < 10; i++){
        temp3 = i;
        temp2 = !temp2;
        GPIOA->ODR ^= 1 << 5;
    } 
    temp1 = -1;
    a = 167;
    fun(a);
    GPIOA->ODR ^= 1 << 5;
    

}

abc::~abc()
{
}

void abc::fun(int &e){

    uint8_t temp = 21;
    e = temp;
}