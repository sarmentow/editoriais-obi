#include<bits/stdc++.h>
using namespace std ; 

const int maxn = 2e4 + 5 ; 
const int inf = 1e9 + 5 ;

int n, timer, m, c, comp[maxn], q, vis[maxn], bridge[maxn] ;
int tin[maxn], low[maxn], sz[maxn], dist[maxn], dist_dij[maxn] ;  
vector<int> pai[maxn] ;
vector<pair<int,pair<int,int>>> grafo[maxn] ;  

void find_b(int v, int p){

	// dfs lowlink utilizada para achar as pontes 
	tin[v] = low[v] = ++timer ; 

	for(auto a : grafo[v]){
		
		if(a.first == p) continue ; 
		if(tin[a.first]){
			low[v] = min(low[v], tin[a.first]) ; 
			continue ; 
		}

		find_b(a.first, v) ; 

		if(low[a.first] > tin[v]) bridge[a.second.second] = 1 ;
		//marcamos que a aresta atual é uma ponte 

		low[v] = min(low[v], low[a.first]) ; 

	}

}

void dfs(int v, int p){

	// a qual componente cada vértice pertence? qual o tamanho de cada ciclo?
	comp[v] = c ; 
	sz[c]++ ;

	for(auto a : grafo[v]){
		if(a.first == p || vis[a.first] || bridge[a.second.second]) continue ; 
		vis[a.first] = 1 ; 
		dist[c] += a.second.first ; 
		dfs(a.first, v) ; 
	}

}

void dij(int ini){
	
	// achar a menor distância para todos os vértices partindo de ini
	for(int i = 1 ; i <= n ; i++) dist_dij[i] = inf ; 

	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fila ; 
    fila.push({0, ini}) ; 
    dist_dij[ini] = 0 ; 

    while(!fila.empty()){
    	
    	int at = fila.top().second ; fila.pop() ; 

    	for(auto a : grafo[at]){
    		if(dist_dij[a.first] > dist_dij[at] + a.second.first){
    			dist_dij[a.first] = dist_dij[at] + a.second.first ; 
    			fila.push({dist_dij[a.first], a.first}) ; 
    		}
    	}

    } 

}

int find_near(int v, int tam){

	int mn = inf ;   
	dij(v) ;

	for(int i = 1 ; i <= c ; i++){
		if(sz[i] == 1) continue ; // não é ciclo
		if(dist[i] < tam) continue ; // caminho inválido
		int mn_dist = inf ; 
		for(auto a : pai[i]) mn_dist = min(mn_dist, dist_dij[a]) ;
		// qual o vértice mais proximo de mim no ciclo i 
		if(i == comp[v]) mn = min(mn, dist[i]) ; // eu faço parte do ciclo atual
		else mn = min(mn, 2*mn_dist + dist[i]) ; // não faço parte 
	}

	return mn ; 

}

int main(){

	cin >> n >> m ; 

	for(int i = 1 ; i <= m ; i++){
		int a, b, c ; 
		cin >> a >> b >> c ; 
		grafo[a].push_back({b, {c, i}}), grafo[b].push_back({a, {c, i}}) ;
		// ao criar o grafo original devemos salvar o índice da aresta para podermos
		// marcá-la como ponte ou não ponte depois 
	}

	find_b(1, 1) ; // achar tds as pontes 

	for(int i = 1 ; i <= n ; i++){
		if(!vis[i]){
			c++ ; 
			dfs(i, i) ; // quebrar nas componentes 
		}
	}

	for(int i = 1 ; i <= n ; i++){
		for(auto a : grafo[i]){
			if(comp[i] == comp[a.first] || !bridge[a.second.second]) continue ; 
			pai[comp[i]].push_back(i), pai[comp[a.first]].push_back(a.first) ; 
			// achar todos os possíveis vertices de saída para cada componente
		}
	} 

	cin >> q ; 

	for(int i = 1 ; i <= q ; i++){
	 	int x, t ; 
	 	cin >> x >> t ; 
	 	int resp = find_near(x, t) ; 
	 	// esta função irá retornar qual a menor distância que precisamos para
	 	// retornar a x com um trem de tamanho t
	 	// caso retorne infinito não tem uma forma válida  
	 	if(resp == inf) cout << "-1\n" ; 
	 	else cout << resp << "\n" ;  	
	} 

}
