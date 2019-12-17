#include <iostream>
#include <vector>

int fftFwd(std::vector<__int64> list, int i){
    __int64 outi = 0;
    int s = i + 1;
    int j = i;
    int N = list.size();
    while(j < N){
        // 1
        int t = 0;
        while( t < s ){
            if( j >= N )
                break;
            outi += list[j];
            j++;
            t++;
        }
        //skip 0
        j += s;
        if( j >= N )
            break;
        // -1
        t = 0;
        while( t < s ){
            if( j >= N )
                break;
            outi -= list[j];
            j++;
            t++;
        }
         //skip 0
        j += s;
    }

    return outi;
}

// void fft2(std::vector<__int64> list, std::vector<__int64> *out){
//     for( int i = 0; i < out->size(); i++){
//         int outi = fftPartial2(list, i);
//         out->at(i) = std::abs(outi) % 10;
//     }
// }

void fftBack(std::vector<__int64> list, std::vector<__int64> *out, int lim){
    int n  = list.size();

    //out.assign(list.size(), 0); //Erase out vector
    //            0  1   0   -1
    int signK[4] = { 1, 1, -1, -1};
    int k = 1;
    out->at( n - 1 ) = list[n - 1];
    for( int j = n - 2; j >= lim; j-- )
        out->at(j) = out->at(j + 1) + list[j];
    // ====================
    // j + (j + 1) * k < n
    // j * (1 + k) + k < n
    // j < (n - k) / (1 + k)

    //ex. n, (n - 1)/2, (n - 2)/3, (n - 3)/4 ...
    //int s = n - 1;
    int s = (n - k) / ( k + 1) + 1;
    //std::cout << "Completed first half " << std::endl;
    while( s >= lim ){
        int r = n - (s + (s + 1) * k);

        if( r < 0 ){
            s--;
            continue;
        }
        k++;

        // if( k > kLim )
        //     return s;

        int sk = signK[ k % 4 ];
        __int64 p = 0;
        int c = n - 1;
        for(int i = 0; i < r; i++){
            p += list[c];
            c --;
        }
        for( int j = s; j >= lim; j--){
            out->at(j) += sk * p;
            if( j == 0 )
                break;
            for( int i = 0; i < k; i++ ){
                p += list[c];
                c--;
            }
        }
        // if( k % 1000 == 0)
        //     std::cout << "Completed k =  " << k << std::endl;
    }

    // for(int i = 0; i < list.size(); i++)
    //     out->at(i) = std::abs(out->at(i)) % 10;

   // return 0;
}

void sFFT(std::vector<__int64> list, std::vector<__int64> *out, int lim){
    // int lim = (list.size() - k) / ( k + 1);
    // if( lim < 0 )
    //     lim = 0;
    fftBack(list, out, lim);

    // for(int j = 0; j < lim; j++){
    //     out->at(j) = fftFwd(list, j);
    // }

    for(int i = lim; i < list.size(); i++)
        out->at(i) = std::abs(out->at(i)) % 10;
}

int main() {
    char digit;
    std::vector<__int64> list;

    while( std::cin >> digit ){
        list.push_back( digit - '0');
    }
    

    int times = 10000;
    //int k = 2; // 100 : 7, 200 : 4, 400 : 2, 800 : < 2
    //int k = 8;

    int index = 0;
    int p10 = 1;
    for( int i = 6; i >= 0; i--){
        index += list[i] * p10;
        p10 *= 10;
    }

    for(int i = 0; i < 7; i++)
        std::cout << list[i];
    std::cout << std::endl;

    std::cout << index << std::endl;

    int len = list.size();
    for(int i = 0; i < times - 1; i++){
        for( int j = 0; j < len; j++)
            list.push_back( list[j] );
    }

    std::vector<__int64> out;
    out.assign(list.size(), 0);

    int k = index;
    int phases = 100;
    //std::cout << "Computing FFTs" <<std::endl;
    for( int p = 0; p < phases; p++){
        sFFT(list, &out, k);
        std::cout << "Completed phase " << p << std::endl;
        
        //  for(int i = 0; i < 20; i++)
        //     std::cout << list[i];
        // std::cout << std::endl;

        std::copy(out.begin() + index, out.end(), list.begin() + index);
    }
    
    for(int i = 0; i < 8; i++)
        std::cout << list[i + index];
    std::cout << std::endl;

    // list2.assign(list.size(), 0);

    // std::copy ( list.begin(), list.end(), list2.begin() );


    // std::cout << list.size() << std::endl;



    // int a = fftPartial(list, 3, 1);
    // int b = fftPartial2(list, 3, 1);

    // std::cout << a << " == " << b << std::endl;

    // int phases = 1;

    // for( int p = 0; p < phases; p++){
    //     fft(list, &out, 1);
    //     std::copy(out.begin(), out.end(), list.begin());
    // }

    // for(int i = 0; i < 8; i++)
    //     std::cout << list[i];
    // std::cout << std::endl;
    
    // for( int p = 0; p < phases; p++){
    //     fft2(list2, &out, 1);
    //     std::copy(out.begin(), out.end(), list2.begin());
    // }

    // for(int i = 0; i < 8; i++)
    //     std::cout << list2[i];
    // std::cout << std::endl;

    return 0;
} 