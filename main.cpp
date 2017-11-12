//
//  main.cpp
//  Ajedres
//
//  Created by michel lopez on 09/11/17.
//  Copyright © 2017 michel lopez. All rights reserved.
//

#include <iostream>


int tabla [8][8] = { {-8,-6,-7,-9,-10,-7,-6,-8},
                     {-5,-5,-5,-5,-5,-5,-5,-5},
                     {0,0,5,5,5,0,0,0},
                     {0,0,5,10,5,0,0,0},
                     {0,0,5,5,5,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {5,5,5,5,5,5,5,5},
                     {8,6,7,9,10,7,6,8}};

int isLetra(char c){
    
    switch (c){
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        case 'h': return 7;
        default:
            return -1;
    }
}

int isNumero(char c){
    switch (c){
        case '1': return 7;
        case '2': return 6;
        case '3': return 5;
        case '4': return 4;
        case '5': return 3;
        case '6': return 2;
        case '7': return 1;
        case '8': return 0;
        default:
            return -1;
    }
}

struct Movimiento {
    int C1;
    int F1;
    int C2;
    int F2;
    
    int pieza;
    int valida1;
    bool valida;
};

Movimiento nuevaP (int n, int b){
    Movimiento p;

    return p;
}

Movimiento analiza(std::string accion){
    //std::string accion = "h5tob6";
    
    Movimiento m;
    
    bool continua = true;
    int i=0;
    int edo=0;
    int varRetorno=0;
    char c = '0';
    
    while (continua){
        c = accion[i];
        switch (edo) {
            case 0:
                varRetorno = isLetra(c);
                
                if ( varRetorno+1 ){
                    m.C1 = varRetorno;
                    //std::cout<< "Si es letra";
                }
                else{
                    std::cout << "No es letra 0";
                    continua = false;
                }
                edo=1;
                break;
            case 1:
                varRetorno = isNumero(c);
                if ( varRetorno+ 1 ){
                    m.F1 = varRetorno;
                    //std::cout<< "Si es Numero";
                }
                else{
                    std::cout << "No es letra 1";
                    continua=false;
                }
                edo=2;
                break;
            case 2:
                //c --> t
                if (c != 't'){
                    std::cout << "No es letra 2.2";
                    continua=false;
                }
                edo=3;
                break;
            
            case 3:
                    if (c != 'o'){
                        std::cout << "No es letra 2.1";
                        continua=false;
                    }
                edo=4;
                break;
                
            case 4:
                varRetorno = isLetra(c);
                
                if ( varRetorno+1 ){
                    m.C2 = varRetorno;
                    //std::cout<< "Si es letra";
                }
                else{
                    std::cout << "No es letra 4";
                    continua = false;
                }
                edo=5;
                break;
                
            case 5:
                varRetorno = isNumero(c);
                if ( varRetorno+ 1 ){
                    m.F2 = varRetorno;
                    //std::cout<< "Si es Numero";
                }
                //std::cout<< "Entrada valida";
                continua=false;
                edo=6;
                break;
                
            default:
                break;
        }
        i++;
    }
    
    if (edo == 6){
        m.valida = true;
    }
    else{
        m.valida = false;
    }
    
    return m;
}

Movimiento valiPieza(Movimiento m){
    int p;
    p = tabla[m.F1][m.C1];
    
    if (p == 0)
        std::cout<< "Error de pieza elegida";
    else
    m.pieza = p;
    
    return m;
}

void moverCaballo(Movimiento m ){
 
    int val = 0;
    
    if ( (std::abs(m.F2 -m.F1)== 1 && std::abs(m.C2 -m.C1)== 2 ) ||
        (std::abs(m.F2 -m.F1)== 2 && std::abs(m.C2 -m.C1)== 1 )  ){
        
        val = tabla[m.F2][m.C2];
        if ( val == 0 ){
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            if (val * m.pieza < 0 ){
                tabla[m.F2][m.C2] = m.pieza;
                tabla[m.F1][m.C1] = 0;
            }
            else{
                std::cout<< "Error de pieza atacada";
            }
        }
    }
    
}

void moverPeon(Movimiento m){
    if ( ( (m.C2 - m.C1 <= 1) &&  (m.C2 - m.C1 >= -1 )  && std::abs(m.F2 -m.F1)== 1 ) ){
        if ( m.F1 > m.F2  && m.pieza >0 ){
            //std::cout<<"Mover peon positivo adelante";
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            if ( m.F1 < m.F2  && m.pieza < 0 ){
                //std::cout<<"Mover peon negativo adelante";
                tabla[m.F2][m.C2] = m.pieza;
                tabla[m.F1][m.C1] = 0;
            }
        }
        
    }
}

Movimiento movimientosGeneralizados(int sign1, int sign2, Movimiento m){
    int temp1,temp2;
    temp1=0;
    temp2=0;
    while((m.F1+temp1!=m.F2)||(m.C1+temp2!=m.C2)){
        if(tabla[m.F1+temp1*sign1][m.C1+temp2*sign2]==0){
            temp1=temp1+sign1;
            temp1=temp2+sign2;
            m.valida1=1;
        }
        else{
            std::cout<< "Error de colision";
            m.valida1=0;
            
            break;
        }
    }
    return m;
}

void moverAlfil(Movimiento m){
    int sign1,sign2;
    int val = 0;
    
    sign1 = m.F2 - m.F1;
    if(sign1!=0){
        sign1 = std::abs(sign1)/sign1;
    }
    sign2 = m.C2 - m.C1;
    if(sign2!=0){
        sign2 = std::abs(sign2)/sign2;
    }
    
    if ( std::abs(m.F2 - m.F1) ==  std::abs(m.C2 - m.C1)){
        val = tabla[m.F2][m.C2];
        if ( val == 0 ){
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            movimientosGeneralizados(sign1,sign2,m);
            if(m.valida1){
                if (val * m.pieza < 0 ){
                    tabla[m.F2][m.C2] = m.pieza;
                    tabla[m.F1][m.C1] = 0;
                }
                else{
                    std::cout<< "Error de pieza atacada";
                }

            }
            
        }
        
    }

}

void moverTorre(Movimiento m){
    int sign1,sign2;
    int val = 0;
    
    sign1 = m.F2 - m.F1;
    if(sign1!=0){
        sign1 = std::abs(sign1)/sign1;
    }
    sign2 = m.C2 - m.C1;
    if(sign2!=0){
        sign2 = std::abs(sign2)/sign2;
    }
    
    if ( (m.F2 == m.F1) ||  (m.C2 == m.C1)){
        val = tabla[m.F2][m.C2];
        if ( val == 0 ){
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            movimientosGeneralizados(sign1,sign2,m);
            if(m.valida1){
                if (val * m.pieza < 0 ){
                    tabla[m.F2][m.C2] = m.pieza;
                    tabla[m.F1][m.C1] = 0;
                }
                else{
                    std::cout<< "Error de pieza atacada";
                }
                
            }
            
        }
        
    }
    //if (posvalidadeTorre)
    movimientosGeneralizados(sign1,sign2,m);
}

void moverReina(Movimiento m){
    int sign1,sign2;
    int val = 0;
    
    sign1 = m.F2 - m.F1;
    if(sign1!=0){
        sign1 = std::abs(sign1)/sign1;
    }
    sign2 = m.C2 - m.C1;
    if(sign2!=0){
        sign2 = std::abs(sign2)/sign2;
    }
    
    
    if ( (std::abs(m.F2 - m.F1) ==  std::abs(m.C2 - m.C1))||(m.F2 == m.F1) ||  (m.C2 == m.C1)){
        val = tabla[m.F2][m.C2];
        if ( val == 0 ){
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            movimientosGeneralizados(sign1,sign2,m);
            if(m.valida1){
                if (val * m.pieza < 0 ){
                    tabla[m.F2][m.C2] = m.pieza;
                    tabla[m.F1][m.C1] = 0;
                }
                else{
                    std::cout<< "Error de pieza atacada";
                }
                
            }
            
        }
    }

}

void moverRey(Movimiento m){
    int sign1,sign2;
    int val = 0;
    
    sign1 = m.F2 - m.F1;
    if(sign1!=0){
        sign1 = std::abs(sign1)/sign1;
    }
    sign2 = m.C2 - m.C1;
    if(sign2!=0){
        sign2 = std::abs(sign2)/sign2;
    }
    if ( ((std::abs(m.F2-m.F1)==1||std::abs(m.F2-m.F1)==0))&&(std::abs(m.C2-m.C1)==1||std::abs(m.C2-m.C1)==0)){
        val = tabla[m.F2][m.C2];
        if ( val == 0 ){
            tabla[m.F2][m.C2] = m.pieza;
            tabla[m.F1][m.C1] = 0;
        }
        else{
            movimientosGeneralizados(sign1,sign2,m);
            if(m.valida1){
                if (val * m.pieza < 0 ){
                    tabla[m.F2][m.C2] = m.pieza;
                    tabla[m.F1][m.C1] = 0;
                }
                else{
                    std::cout<< "Error de pieza atacada";
                }
                
            }
            
        }
    }

}

Movimiento valiMovi(Movimiento m){
    
    switch ( std::abs(m.pieza) ) {

        case 5:
            moverPeon(m);
            break;
        case 6:
            moverCaballo(m);
            break;
        case 7:
            moverAlfil(m);
            break;
        case 8:
            moverTorre(m);
            break;
        case 9:
            moverReina(m);
        case 10:
            moverRey(m);
        default:
            break;
    }
    return m;
}

void display()
{
    int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        std::cout<<tabla[i][j]<<",";
        //printf("%c",board[i][j]);
        //printf("%d",i);
        //printf("\n");
        std::cout<<std::endl;
    }
    
}

int main(int argc, const char * argv[]) {
    
    display();
    
    //std::string accion = "b1toc3"; // mov caballo
    //std::string accion = "d5tod6"; // mov peon
    //std::string accion = "d5tob7"; // mov alfil
    //std::string accion = "d5tod7"; // mov torre
    //std::string accion = "d5toe4"; // mov reyna
    std::string accion = "d5tod6"; // mov rey
    
    Movimiento m1;
    
    m1 = analiza(accion);
    
    if (m1.valida){
        m1=valiPieza(m1);
        if (m1.pieza != 0 ){
            valiMovi(m1);
        }
        else{
            std::cout<<"Error de movimiento";
        }
    }
    else{
        std::cout<<"Error de entrada incorrecta";
    }
    std::cout << "Hello, World!\n";
    display();
    return 0;
}
