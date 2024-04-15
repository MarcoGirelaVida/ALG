#include <iostream>
#include <vector>
#include <stack>

using namespace std;


vector<int> Gasolineras(int k, stack<int> G, int n){

    vector<int> S(1,0);
    int d = 0,i;

    while(!G.empty()){
        i = G.top();
        G.pop();
        d = i - S.back();
        if((G.top() - i) > (k - d)){
            S.push_back(i);
        }
        if(G.size() == 1) G.pop();
    }
    return S;
}


int main(int argc, char *argv[]){
    if(argc < 4){
        cout << "Modo de empleo: Ejecutable Max_distancia Distancia_destino G1 G2 G3 ... Gn\n";
    }

    int max_dist = atoi(argv[1]);
    int dist_dest = atoi(argv[2]);

    stack<int> gasolineras;
    for(int i = argc - 1; i > 2; i--){
        gasolineras.push(atoi(argv[i]));
    }
    cout << "\n";
    vector<int> S = Gasolineras(max_dist,gasolineras,dist_dest);

    cout << "Paradas en la ruta:\n";
    for(int i = 0; i < S.size(); i++){
        cout << "Parada " << i << ": " << S[i] << endl;
    }

}