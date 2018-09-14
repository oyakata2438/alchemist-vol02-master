= 数理最適化サンプルプログラムを軽く解析して今後の応用に備える @ matchbou

== はじめに

大昔の大学受験参考書「チャート式」とか「解法のテクニック」みたいにオペレーションズリサーチの典型問題のパターン毎にサンプルプログラムをそろえて、実行例としてのサンプルデータの内容も含めて整理すれば、今後の業務応用前の予習になるかとトライしてみました。

== 組み合わせ最適化手法の典型問題列挙と整理

ありがたいことに@SaitoTsutomuさんが

https://qiita.com/SaitoTsutomu/items/0f6c1a4415d196e64314

にまとめられていますので、引用させていただきます。
というか、これなしには、私の中では、実務とOR教科書の例題が結びつきませんでした…orz。

//image[Table1][本章で取り扱うORの典型問題]

実行環境は、Windows 10 Pro, Python3.5（Anaconda）を前提とします。


== グラフ・ネットワーク問題

「グラフ」
地下鉄の路線図のように「点（ノード：路線図の駅）」とそれを結ぶ「辺（エッジ：路線図の線路）」からなるもの。
辺の方向性の有無で有向グラフと無向グラフに分類される。

//image[image1][有向グラフと無向グラフ]

また、点や辺に重みを付与する場合もある

//image[image2][重み付きグラフの例][scale=0.8]

=== 最小全域木問題（＃１）

適切な辺を経由することで全ての点の間を移動できる閉路（輪）のないグラフ（木：@<img>{image3}）において、上右図2のように辺に重みがある場合に重みの和を最小にするもの。

//image[image3][様々な木]

==== 最小全域木問題の応用例

 * 最小コストでのLANケーブル配線（点はコンピュータ

==== 最小全域木問題のサンプルプログラムと用いているデータ構造の解説

//listnum[No1][最小全域木問題]{
###https://qiita.com/SaitoTsutomu/items/3130634debf561608bd9
from more_itertools import first, pairwise
# CSVデータ
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw
node = pd.read_csv('./node0.csv')
edge = pd.read_csv('./edge0.csv')

# グラフ描画
g = graph_from_table(node, edge)[0] #読み込んだデータからベースグラフを作成
t = nx.minimum_spanning_tree(g) #上記グラフ中の全域最小木を求める
pos = networkx_draw(g) #ortoolpyの関数でベースグラフを描画
nx.draw_networkx_edges(t, pos, width=3) #更に全域最小木を太字（width=3）でプロット
plt.show() #さあ表示！！
//}

//image[image4][#1最小全域木問題のグラフ][scale=0.5]

==== データの説明

Node：上記グラフに於ける（頂）点データ。idは頂点の識別番号、x,yは便宜的表示用の座標軸上位置

//image[table2][最小全域木問題におけるノードデータ][scale=0.75]

Edge：上記グラフに於ける辺データ。
表示されているnode1とnode2の組み合わせに辺がある。
Weightは辺重みを表す。Weight列がない場合は、nodeデータ座標軸のユークリッド距離を用いる。

//image[table3][最小全域木問題におけるエッジデータ][scale=0.75]

=== 最大安定集合問題（最小頂点被覆問題, 補グラフの最大クリーク問題）（＃２）

最大安定集合問題：互いに直結する辺が存在しない頂点の集合で最大の個数をもつ集合を求める問題。
論理的に最大クリーク問題と等価であり、且つ最小頂点被覆問題とも等価である
最小頂点被覆問題：すべての辺のいずれか一端が接する頂点集合のうち個数が最小のものを求める問題。
最大クリーク問題：頂点同士を直結する辺が存在する頂点グループの内、頂点の個数が最大を求めるもの。
計算量クラスNP困難の為、ヒューリスティックに解を求めるアルゴリズムの探索は研究対象となっている。

//image[image5][最大安定集合問題のいくつかのパターン]

==== 最大安定集合問題の応用例

データ分析に於けるクラスタリング手法のひとつとして

==== 最大安定集合問題のサンプルプログラムと用いているデータ構造の解説

//listnum[No2][最大安定集合問題]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw, maximum_stable_set
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac1.csv')
g = graph_from_table(tbn, tbe)[0]
t = maximum_stable_set(g)
pos = networkx_draw(g, node_color='white')
nx.draw_networkx_nodes(g, pos, nodelist=t[1])
plt.show()
print(t)
//}

//image[image6][最大安定集合問題のグラフ][scale=0.5]

Node：上記グラフに於ける（頂）点データ。idは頂点の識別番号、x,yは便宜的な座標軸上の位置

//image[table4][最大安定集合問題におけるノードデータ][scale=0.75]

表示されているnode1とnode2の組み合わせに辺がある。
辺の重みを表すWeightは自明であるが不要。

//image[table5][最大安定集合問題における辺データ][scale=0.75]

==== 最小頂点被覆問題

//listnum[No2-2][最小頂点被覆問題のコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw, min_node_cover
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac1.csv')
g = graph_from_table(tbn, tbe)[0]
t = min_node_cover(g)
pos = networkx_draw(g, node_color='white')
nx.draw_networkx_nodes(g, pos, nodelist=t)
plt.show()
print(t)
//}

//image[image7][最小頂点被覆問題のグラフ][scale=0.5]

データは、最大集合安定問題と同じ。

==== 最大クリーク問題（TBW）
最大クリーク問題は、グラフ理論において、グラフ中のクリーク（任意の二頂点間に辺があるような頂点集合）の中で最大のものを見つける問題。

=== 最大カット問題 （＃３）

グラフ上の頂点をグループ分けするときにグループの分かれ目上にある辺の重み総和が最大となるグルーピングを求める問題。

//image[image8][最大カット問題の概念図]

==== 最大カット問題の応用例

画像の領域抽出（CT画像から臓器の領域のみくりぬく）。
配送担当領域の分割（辺の重みがその間を通る交通のコストと看做した場合など）

==== 最大カット問題のサンプルコードとデータ構造の解説

//listnum[No3][最大カット問題のサンプルコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw, maximum_cut
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac1.csv')
g = graph_from_table(tbn, tbe)[0]
t = maximum_cut(g)
pos = networkx_draw(g, node_color='white')
nx.draw_networkx_nodes(g, pos, nodelist=t[1])
plt.show()
print(t)
//}

//image[table6][最大カット問題のノード][scale=0.75]

//image[table7][最大カット問題の辺][scale=0.75]

Node: 最小全域木問題のNodeデータと同じ。

Edge: 最小全域木問題のEdgeデータと同じ。node1,node2でどの辺かを示し、weightで重みを与える。

=== 最短路問題（＃４）

辺に重みのついたグラフで任意の頂点aから別の任意の頂点bへの最短経路（=通過する辺の重みが最小）

==== 最短経路問題の応用例

サプライチェーンにおける最短経路の探索

==== 最短経路問題のサンプルプログラムとデータ

//listnum[No4][最短経路問題のサンプルコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw, maximum_stable_set
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac1.csv')
g = graph_from_table(tbn, tbe)[0]
route=nx.dijkstra_path(g, 5, 2, weight='weight')# node5と2の間の最短路を求める
print(route)
pos = networkx_draw(g, node_color='white')
nx.draw_networkx_nodes(g, pos, nodelist=route)
plt.show()
//}

//image[image9][最短経路問題のグラフ][scale=0.5]

データの解説：最大カット問題と同じ。

=== 最大流問題（＃５）

単一の始点から単一の終点へのフローネットワークで最大となるフローを求める問題。

==== 最大流問題の応用例

サプライチェーンで、とある配送元から配送先に輸送できる最大量の探索など

==== 最大流問題のサンプルコード

//listnum[No5][最大流問題のサンプルコード]{
import pandas as pd, networkx as nx
import matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0.csv')
g = graph_from_table(tbn, tbe)[0]
t = nx.maximum_flow(g, 5, 2)
pos = networkx_draw(g)
nx.draw_networkx_edges(g, pos, width=3, edgelist
  =[(k1, k2) for k1, d in t[1].items() for k2, v in d.items() if v])
plt.show()
for i, d in t[1].items():
    for j, f in d.items():
        if f: print((i, j), f)
//}

//image[image10][最大流問題のグラフ][scale=0.5]

//image[table8][最大流問題のノード][scale=0.75]

//image[table9][最大流問題のエッジ][scale=0.75]

Node:最大カット問題のデータと同じ

Edge:流量の上限制約であるcapacity変数を含む

=== 最小費用流問題（＃６）
決まった量をネットワーク上で始点から終点まで流す際にかかる費用（コスト）を最小にしようという問題

==== 最小費用流問題の応用
商品配送網でのコスト削減施策の検討等。


==== 最小費用流問題のサンプルコード
//listnum[No6][最小費用流問題のサンプルコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw
tbn = pd.read_csv('./node0mac2.csv')
tbe = pd.read_csv('./edge0.csv')
g = graph_from_table(tbn, tbe, directed=True)[0]
pos = networkx_draw(g)
result = nx.min_cost_flow(g)
nx.draw_networkx_edges(g, pos, width=3, edgelist
  =[(k1, k2) for k1, d in result.items() for k2, v in d.items() if v])
nx.draw_networkx_edge_labels(g, pos,
    edge_labels=dict([ ((k1, k2),v) for k1, d in result.items() /for k2, v in d.items() if v])
                            )
plt.show()
//}

//image[image11][最小費用流問題のグラフ][scale=0.5]

//image[table10][最小費用流問題のノード][scale=0.75]

//image[table11][最小費用流問題のエッジ][scale=0.75]

Node:各頂点の需要量がdemand列に表される

Edge:最大流問題と同じ。



== 経路問題

グラフの点を巡回箇所、辺を点の間を結ぶ通路と捉えて、与えられた目的関数を最大化（最小化）するために使用する通路とその順番を定める問題の総称。

=== 運搬経路（配送最適化）問題[Vehcle Routing Problem]（＃７）
複数のサービス車（Vehicle）がスタート地点から需要のある地点の巡回を行いゴール地点へ行く。全ての需要を満たし、総経路コストを最小化することを考える問題
==== 運搬経路問題の応用例
説明どおりの配送網に於ける複数台のトラックへの配送物割り当ての他、複数人が働く倉庫での資材取り出しに於ける作業員への振り分け等。
運搬経路最適化

==== 運搬経路問題のサンプルコードとデータ

//listnum[No7][運搬経路問題のサンプルコード]{
import pandas as pd, networkx as nx
import matplotlib.pyplot as plt
from ortoolpy import vrp, graph_from_table, networkx_draw
tbn = pd.read_csv('./node1.csv')
tbe = pd.read_csv('./edge1.csv')
g = graph_from_table(tbn, tbe)[0].to_directed()
networkx_draw(g)
plt.show()
nv, capa = 2, 3 # 車両数、車両容量
print(vrp(g, nv, capa))
//}

//image[image12][運搬経路問題のグラフ][scale=0.5]

//image[table12][運搬経路問題のノード][scale=0.75]

//image[table13][運搬経路問題のエッジ][scale=0.75]

Node:最小費用流問題と異なり、発地の需要がマイナスとなっておらずゼロである。

Edge:配送ルート毎のコストを保持している。







=== 巡回セールスマン問題（＃８）

巡回セールスマン問題（英: traveling salesman problem、TSP）は、都市の集合と各2都市間の移動コスト（たとえば距離）が与えられたとき、全ての都市をちょうど一度ずつ巡り出発地に戻る巡回路の総移動コストが最小のものを求める（セールスマンが所定の複数の都市を1回だけ巡回する場合の最短経路を求める）組合せ最適化問題。

==== 巡回セールスマン問題の応用例

まさにサプライチェーンの業務効率化に資する問題そのもの

==== 巡回セールスマン問題のサンプルプログラムとデータ
NP困難な問題の解法として種々のヒューリスティックな方法がありますが、今回は私的に耳に新しい蟻コロニー最適化（ACO）による解法のプログラムをみてみます。蟻が巣に物資を運ぶ際の最適経路選定に用いている方法の援用のようです。

//listnum[no8][巡回セールスマン問題のサンプルプログラム]{
#巡回セールスマン問題を蟻コロニー最適化と遺伝的アルゴリズムで解いてみる[Python]
#http://tony-mooori.blogspot.com/2016/02/tsppython.html
#coding:utf-8
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.spatial import distance as dis
"""
参考URL
[1] 蟻コロニー最適化 - Wikipedia https://ja.wikipedia.org/wiki/蟻コロニー最適化
[2] 任意の確率密度分布に従う乱数の生成（von Neumannの棄却法） | Pacocat's Life http://pacocat.com/?p=596
"""
class TSP:
    def __init__(self,path=None,alpha = 1.0,beta = 1.0,Q = 1.0,vanish_ratio = 0.95):
        """ 初期化を行う関数 """
        self.alpha = alpha                    # フェロモンの優先度
        self.beta = beta                    # ヒューリスティック情報(距離)の優先度
        self.Q = Q                            # フェロモン変化量の係数
        self.vanish_ratio = vanish_ratio    # 蒸発率
        if path is not None:
            self.set_loc(np.array(pd.read_csv(path)))
    
    def set_loc(self,locations):
        """ 位置座標を設定する関数 """
        self.loc = locations                            # x,y座標
        self.n_data = len(self.loc)                        # データ数
        self.dist = dis.squareform(dis.pdist(self.loc))    # 距離の表を作成
        self.weight = np.random.random_sample((self.n_data,self.n_data))  # フェロモンの量
        self.result = np.arange(self.n_data)            # もっともよかった順序を保存する
        print("x,y座標")
        print(self.loc)
        #print(self.n_data)
        print("距離の表")
        print(self.dist)
        #print(self.weight)
        #print(self.result)
        
    def cost(self,order):
        """ 指定された順序のコスト計算関数 """
        n_order = len(order)
        return np.sum( [ self.dist[order[i],order[(i+1)%n_order]] for i in np.arange(n_order) ] )
    
    def plot(self,order=None):
        """ 指定された順序でプロットする関数 """
        if order is None:
            plt.plot(self.loc[:,0],self.loc[:,1])
        else:
            plt.plot(self.loc[order,0],self.loc[order,1])
        plt.show()
    
    def solve(self,n_agent=1000):
        """ 巡回セールスマン問題を蟻コロニー最適化で解く """
        
        order = np.zeros(self.n_data,np.int)         # 巡回経路
        delta = np.zeros((self.n_data,self.n_data))    #フェロモン変化量
        
        for k in range(n_agent):
            city = np.arange(self.n_data)
            now_city = np.random.randint(self.n_data)    # 現在居る都市番号
            
            city = city[ city != now_city ]
            order[0] = now_city
            
            for j in range(1,self.n_data):
                upper = np.power(self.weight[now_city,city],self.alpha)*np.power(self.dist[now_city,city],-self.beta)
                
                evaluation = upper / np.sum(upper)                # 評価関数
                percentage = evaluation / np.sum(evaluation)    # 移動確率
                index = self.random_index(percentage)            # 移動先の要素番号取得
                
                # 状態の更新
                now_city = city[ index ]
                city = city[ city != now_city ]
                order[j] = now_city
            
            L = self.cost(order) # 経路のコストを計算
            
            # フェロモンの変化量を計算
            delta[:,:] = 0.0
            c = self.Q / L
            for j in range(self.n_data-1):
                delta[order[j],order[j+1]] = c
                delta[order[j+1],order[j]] = c
            
            # フェロモン更新
            self.weight *= self.vanish_ratio 
            self.weight += delta
            
            # 今までで最も良ければ結果を更新
            if self.cost(self.result) > L:
                self.result = order.copy()
            
            # デバッグ用
            print("Agent ... %d , Cost ... %lf" % (k,self.cost(self.result)))
        
        return self.result

    
    def random_index(self,percentage):
        """ 任意の確率分布に従って乱数を生成する関数 """
        n_percentage = len(percentage)
        
        while True:
            index = np.random.randint(n_percentage)
            y = np.random.random()
            if y < percentage[index]:
                return index
      
if __name__=="__main__":
    tsp = TSP(path="node0mac3-only-xy-figure.csv")
    tsp.solve(n_agent=1000)        # 1000匹の蟻を歩かせる
    tsp.plot(tsp.result)        # 計算後
    plt.show()
//}

出力
//listnum[no8-out][巡回セールスマン問題の出力]{
x,y座標
[[ 5  8]
 [10  5]
 [ 7  0]
 [ 2  2]
 [ 0  5]]
距離の表
[[  0.           5.83095189   8.24621125   6.70820393   5.83095189]
 [  5.83095189   0.           5.83095189   8.54400375  10.        ]
 [  8.24621125   5.83095189   0.           5.38516481   8.60232527]
 [  6.70820393   8.54400375   5.38516481   0.           3.60555128]
 [  5.83095189  10.           8.60232527   3.60555128   0.        ]]
Agent ... 0 , Cost ... 26.483572
Agent ... 1 , Cost ... 26.483572
Agent ... 2 , Cost ... 26.483572
Agent ... 3 , Cost ... 26.483572
…
Agent ... 995 , Cost ... 26.483572
Agent ... 996 , Cost ... 26.483572
Agent ... 997 , Cost ... 26.483572
Agent ... 998 , Cost ... 26.483572
Agent ... 999 , Cost ... 26.483572
//}

//image[image13][巡回セールスマン問題の出力][scale=0.5]

//image[table14][巡回セールスマン問題のノード][scale=0.75]

Nodeデータのみです。列名、行名無です。左からx座標とy座標

==== 巡回セールスマン問題の感想
本件では、入力データのxy座標からユークリッド距離を生成しています。
地点間の距離を任意に投入したい場合は、プログラム中の「距離の表を作成」のところを改変して、地点間距離データを投入することで対応可能と思量します。そうすれば、実務上は必ずしもユークリッド距離に拠らない、輸送料金での最適化なども可能と思量します。


=== 中国人郵便配達問題（＃９）

全ての頂点間をいずれかの辺を通って（必ずしも直結する辺が存在するとは限らない、また辺には重みがある）移動できるときに全ての辺を通り重みの合計が最小となる通り方を求める問題。

==== 中国人郵便配達問題の応用例

まさに郵便配達に類するサプライチェーン問題にどうぞ

==== 中国人郵便配達問題のサンプルコード

//listnum[No9][中国人郵便配達問題のサンプルコード]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import chinese_postman, graph_from_table, networkx_draw
tbn = pd.read_csv('./node0mac1.csv')
tbe = pd.read_csv('./edge0mac2.csv')
g = graph_from_table(tbn, tbe, multi=True)[0]
networkx_draw(g)
plt.show()
print("重み合計とルート順表示")
print(chinese_postman(g))
//}

//image[image14][中国人郵便配達問題の出力]

重み合計とルート順表示
//listnum[No9-out][出力:重み合計とルート順表示]{
(36, [(0, 4), (4, 5), (5, 4), (4, 3), (3, 2), (2, 3), (3, 0), (0, 5), (5, 1), (1, 2), (2, 0), (0, 1), (1, 0)])
//}

//image[table15][中国人郵便配達問題の問題のノード][scale=0.75]

//image[table16][中国人郵便配達問題の問題のエッジ][scale=0.75]

ノード間の重み（Weight)情報は、ノードテーブルの方に格納される。


== 集合被覆・分割問題
=== 集合被覆問題（＃１０） 

集合の部分集合毎にコストが与えられているときに最小コストで集合の全要素をカバーできるような部分集合の組み合わせを選択する。（複数の部分集合でカバーされている要素があっても構わない）

==== 集合被覆問題の応用例
乗務員スケーリング問題等。

==== 集合被覆問題のサンプルプログラムとデータ
//listnum[No10-1][集合被覆問題のサンプルコード1]{
def set_cover(universe, subsets):
    """Find a family of subsets that covers the universal set"""
    """http://www.martinbroadhurst.com/greedy-set-cover-in-python.html"""
    elements = set(e for s in subsets for e in s)
    # Check the subsets cover the universe
    if elements != universe:
        return None
    covered = set()
    cover = []
    # Greedily add the subsets with the most uncovered points
    while covered != elements:
        subset = max(subsets, key=lambda s: len(s - covered))
        cover.append(subset)
        covered |= subset
 
    return cover
 
def main():
    universe = set(range(1, 11))
    subsets = [set([1, 2, 3, 8, 9, 10]),
        set([1, 2, 3, 4, 5]),
        set([4, 5, 7]),
        set([5, 6, 7]),
        set([6, 7, 8, 9, 10])]
    cover = set_cover(universe, subsets)
    print("whole universe")
    print(universe)
    print("given subsets")
    print(subsets)
    print("cover:chosen subsets")
    print(cover)

if __name__ == '__main__':
    main()
//}

//listnum[No10-2][集合被覆問題の出力1]{
出力：上から全集合、被覆する為に用いる部分集合、解答として選ばれた部分集合群
whole universe
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
given subsets
[{1, 2, 3, 8, 9, 10}, {1, 2, 3, 4, 5}, {4, 5, 7}, {5, 6, 7}, {8, 9, 10, 6, 7}]
cover:chosen subsets
[{1, 2, 3, 8, 9, 10}, {4, 5, 7}, {5, 6, 7}]
//}

//listnum[No10-3][集合被覆問題のサンプルその2]{
import pandas as pd
from ortoolpy import set_covering
ss = pd.read_csv('./subset.csv')
g = ss.groupby('id')
print(‘結果’)
set_covering(len(g), [(r.weight.iloc[0], r.element.tolist()) for _, r in g])
//}

結果

//image[table17][被覆集合問題のサンプル2の結果][scale=0.75]

//image[image15][被覆集合問題のサンプル2の結果グラフ][scale=0.5]

[0,1,2]
縦持ち形式で、id毎の重みweightとカバーする領域elementの形で与えられる。
a,b,c,dの要素をid0,1,2,3でカバーする際に最小重み和となるのは0,1,2である。


=== 集合分割問題（＃１１）

集合の部分集合毎にコストが与えられているときに最小コストで集合の全要素をカバーできるような部分集合の組み合わせを選択する。（複数の部分集合でカバーされている要素があってはいけない）

==== 集合分割問題の応用例

==== 集合分割問題のサンプルプログラムとデータ
//listnum[No11][集合分割問題のサンプルプログラム]{
import pandas as pd
from ortoolpy import set_partition
ss = pd.read_csv('./subset.csv')
g = ss.groupby('id')
set_partition(len(g), [(r.weight.iloc[0], r.element.tolist()) for _, r in g])
//}

データは、集合被覆問題とおなじ。

//image[image16][集合分割問題の結果][scale=0.5]

[2,3]
a,b,c,dの要素をid2,3でカバーするとコストは先の被覆問題より増加するが,重複が生じない。

=== 組み合わせオークション問題（＃１２）

複数の財を組合せて取得することで個々の財の価値の総和よりも価値が増加したり (補完性)、減少したり (代替性) するような場合に於いては、財を１つずつ別個にオークションに掛ける事が出品者にとって最適な結果をもたらすとは限らない。そのような場合に以下のような手続きで実行される「組合せオークション」に於いて入札額の総和が最大になるように財の割り当てを決める問題である。

(1) 参加者は財の部分集合すべてに対する入札額を申告する

(2) 申告をもとに、主催者は各参加者の入札額の総和が最大になるように財の割当を定める

(3) 参加者は割り当てられた財に対する自分の申告した入札額を主催者に支払う

==== 組み合わせオークション問題のサンプルプログラムとデータ

//listnum[No12][組み合わせオークション問題のサンプルコード]{
from ortoolpy import combinatorial_auction
cand = [
    ( 15, (0,2), 0),
    ( 10, (0,), 1),
    (  8, (1,), 1),
    ( 14, (1,2), 2),
]
#実行
combinatorial_auction(3, cand)
//}

データはプログラムの中で定義されている配列candである。1行目を例にとると
(15,(0,2),0) ⇒ 15は入札価格、(0,2)は入札するゼロ始まりのアイテム番号で、最後の0は購入者ID
である。
combinatorial_auctionの引数は、左より要素数、入札状況データ（上述）、省略されている第3引数が購入者毎の候補数上限である。

//listnum[No12-2][組み合わせオークション問題のサンプル2]{
import numpy as np

def CombinatorialAuction(df, id_label='id', price_label='price',
        element_label='element', buyer_label='buyer', limit=-1, **kwargs):
    """
    組合せオークション問題
        要素を重複売却せず、購入者ごとの候補数上限を超えないように売却金額を最大化
    入力
        df: 候補のDataFrameもしくはCSVファイル名
        id_label: 候補番号の属性文字
        price_label: 金額の属性文字
        element_label: 要素の属性文字
        buyer_label: 購入者番号の属性文字
        limit: 購入者ごとの候補数上限。-1なら無制限。購入者IDをキーにした辞書可
    出力
        選択された候補リストの番号リスト
        (priceは、同一id内で1つ以外NaNと変える)
    """
    df = graph_from_table(df, None, no_graph=True, **kwargs)[1]
    df = df.sort_values(id_label)
    g = df.groupby(id_label)
    r = combinatorial_auction(len(df[element_label].unique()),
        [(v[price_label].iloc[0], v[element_label].tolist(),
          v.iloc[0].get(buyer_label, 0)) for _,v in g], limit=limit)
    df = df[df[id_label].isin(r)].copy()
    df.loc[df[id_label]==df[id_label].shift(1), price_label] = np.nan
    return df

def graph_from_table(dfnd, dfed, directed=False, node_label='id',
        from_label='node1', to_label='node2', from_to=None,
        no_graph=False, **kwargs):
    """表からグラフを作成"""
    import re, pandas as pd, networkx as nx
    class mydict(dict):
        __getattr__ = dict.__getitem__
        __deepcopy__ = lambda i, j: mydict(i)
    if isinstance(dfnd, str):
        m = re.match(r'\[([^]]+)](\w+)', dfnd)
        if m:
            dfnd = pd.read_excel(m.group(1), m.group(2), **kwargs)
        else:
            dfnd = pd.read_csv(dfnd, **kwargs)
    if isinstance(dfed, str):
        m = re.match(r'\[([^]]+)](\w+)', dfed)
        if m:
            dfed = pd.read_excel(m.group(1), m.group(2), **kwargs)
        else:
            dfed = pd.read_csv(dfed, **kwargs)
    g = None
    if not no_graph:
        g = nx.DiGraph() if directed else nx.Graph()
        if dfnd is not None:
            for _,r in dfnd.iterrows():
                g.add_node(r[node_label], mydict(r.to_dict()))
        if from_to:
            dfft = dfed[[from_label,to_label]]
            dfed[from_to] = dfft.min(1).astype(str)+'-'+dfft.max(1).astype(str)
        for _,r in dfed.iterrows():
            n1,n2 = r[from_label],r[to_label]
            g.add_edge(n1, n2, None)
            g.adj[n1][n2] = mydict(r.to_dict())
            (g.pred if directed else g.adj)[n2][n1] = g.adj[n1][n2]
    return g, dfnd, dfed
#サンプル 2-設定1 – limit引数無の設定で実行
CombinatorialAuction('auction5.csv')
//}

//image[tableauction][組み合わせオークション問題のデータ　auction5.csv][scale=1.0]

Idは単なる識別子で値により動作は不変。priceは入札価格、elementは入札対象アイテム名、buyerは入札者識別子。

結果
//image[image12-2][組み合わせオークション問題の結果]

同一buyerに複数（本例は上限なし）アイテムの入札を許し、各elementに最高額を付けた入札が採用される。

//listnum[No12-3][組み合わせオークション問題のサンプルコード:設定2]{
#サンプル 2-設定2 – limit引数1の設定で実行—入札上限は1アイテム
CombinatorialAuction('auction5.csv',limit=1)
//}

結果
//image[image12-3][組み合わせオークション問題　設定2の結果]

各buyerの落札アイテム数が1という制約が課される。

== スケジューリング問題
スケジュールを立てる問題。

=== ジョブショップ問題（＃１３）
与えられたn個のジョブV={1,…,n}をm台の機械で処理する。1つの機械では、同時に1つのジョブしか処理できない。全てのジョブの終了時間を最小にするスケジュールを求める問題。

==== ジョブショップ問題の応用例
生産計画等の現場で仕事（ジョブ）を機械に効率的に割り振る事で，完了時刻，納期遅れ等の最小化を目指す等。

==== ジョブショップ問題のサンプルプログラム
//listnum[No13][ジョブショップ問題のサンプルプログラム]{
###The Job Shop Problem

from __future__ import print_function

# Import Python wrapper for or-tools constraint solver.
from ortools.constraint_solver import pywrapcp

def main():
  # Create the solver.
  solver = pywrapcp.Solver('jobshop')

  machines_count = 3
  jobs_count = 3
  all_machines = range(0, machines_count)
  all_jobs = range(0, jobs_count)
  # Define data.
  machines = [[0, 1, 2],
              [0, 2, 1],
              [1, 2]]

  processing_times = [[3, 2, 2],
                      [2, 1, 4],
                      [4, 3]]
  # Computes horizon.
  horizon = 0
  for i in all_jobs:
    horizon += sum(processing_times[i])
  # Creates jobs.
  all_tasks = {}
  for i in all_jobs:
    for j in range(0, len(machines[i])):
      all_tasks[(i, j)] = solver.FixedDurationIntervalVar(0,
                                                          horizon,
                                                          processing_times[i][j],
                                                          False,
                                                          'Job_%i_%i' % (i, j))

  # Creates sequence variables and add disjunctive constraints.
  all_sequences = []
  all_machines_jobs = []
  for i in all_machines:

    machines_jobs = []
    for j in all_jobs:
      for k in range(0, len(machines[j])):
        if machines[j][k] == i:
          machines_jobs.append(all_tasks[(j, k)])
    disj = solver.DisjunctiveConstraint(machines_jobs, 'machine %i' % i)
    all_sequences.append(disj.SequenceVar())
    solver.Add(disj)

  # Add conjunctive contraints.
  for i in all_jobs:
    for j in range(0, len(machines[i]) - 1):
      solver.Add(all_tasks[(i, j + 1)].StartsAfterEnd(all_tasks[(i, j)]))

  # Set the objective.
  obj_var = solver.Max([all_tasks[(i, len(machines[i])-1)].EndExpr()
                        for i in all_jobs])
  objective_monitor = solver.Minimize(obj_var, 1)
  # Create search phases.
  sequence_phase = solver.Phase([all_sequences[i] for i in all_machines],
                                solver.SEQUENCE_DEFAULT)
  vars_phase = solver.Phase([obj_var],
                            solver.CHOOSE_FIRST_UNBOUND,
                            solver.ASSIGN_MIN_VALUE)
  main_phase = solver.Compose([sequence_phase, vars_phase])
  # Create the solution collector.
  collector = solver.LastSolutionCollector()

  # Add the interesting variables to the SolutionCollector.
  collector.Add(all_sequences)
  collector.AddObjective(obj_var)

  for i in all_machines:
    sequence = all_sequences[i];
    sequence_count = sequence.Size();
    for j in range(0, sequence_count):
      t = sequence.Interval(j)
      collector.Add(t.StartExpr().Var())
      collector.Add(t.EndExpr().Var())
  # Solve the problem.
  disp_col_width = 10
  if solver.Solve(main_phase, [objective_monitor, collector]):
    print("\nOptimal Schedule Length:", collector.ObjectiveValue(0), "\n")
    sol_line = ""
    sol_line_tasks = ""
    print("Optimal Schedule", "\n")

    for i in all_machines:
      seq = all_sequences[i]
      sol_line += "Machine " + str(i) + ": "
      sol_line_tasks += "Machine " + str(i) + ": "
      sequence = collector.ForwardSequence(0, seq)
      seq_size = len(sequence)

      for j in range(0, seq_size):
        t = seq.Interval(sequence[j]);
         # Add spaces to output to align columns.
        sol_line_tasks +=  t.Name() + " " * (disp_col_width - len(t.Name()))

      for j in range(0, seq_size):
        t = seq.Interval(sequence[j]);
        sol_tmp = "[" + str(collector.Value(0, t.StartExpr().Var())) + ","
        sol_tmp += str(collector.Value(0, t.EndExpr().Var())) + "] "
        # Add spaces to output to align columns.
        sol_line += sol_tmp + " " * (disp_col_width - len(sol_tmp))

      sol_line += "\n"
      sol_line_tasks += "\n"

    print(sol_line_tasks)
    print("Time Intervals for Tasks\n")
    print(sol_line)

if __name__ == '__main__':
  main()
//}

//listnum[No13-2][ジョブショップ問題の解]{
出力
Optimal Schedule Length: 11 

Optimal Schedule 
Machine 0: Job_0_0   Job_1_0   
Machine 1: Job_2_0   Job_0_1   Job_1_2   
Machine 2: Job_1_1   Job_0_2   Job_2_1   

Time Intervals for Tasks
Machine 0: [0,3]     [3,5]     
Machine 1: [0,4]     [4,6]     [6,10]    
Machine 2: [5,6]     [6,8]     [8,11]    
//}

=== 勤務スケジューリング問題 （＃１４）
スタッフの人数、スケジュール日数、シフトの種類数、避けるべきシフトのパターン、日ごとのシフトごとの必要数が与えられたときに、これらを満たすスケジュールを求める問題。

==== 勤務スケジューリング問題のサンプルプログラム
//listnum[NO14][勤務スケジューリング問題のサンプルプログラム]{
from ortoolpy import shift_scheduling
ndy, nst = 8, 4
shift = '休日夜'
proh = ['夜夜', '夜日', '日日日']
need = {'日':[2] * 8, '夜':[1] * 8}
r = shift_scheduling(ndy, nst, shift, proh, need)
print(r)

import numpy as np, pandas as pd
a = pd.DataFrame(np.vectorize(lambda i: shift[i])(r),
    columns=[chr(65+i) for i in range(nst)],
    index=['%d日目'%i for i in range(1,ndy+1)])
for sft,lst in need.items():
    a['%s必要'%sft] = lst
    a['%s計画'%sft] = (a.iloc[:,:4]==sft).sum(1)
print(a)
//}

//image[table18][勤務スケジューリング問題の解][scale=0.5]

== 切り出し・詰め込み問題
容量と品物(価値や体積)が与えられたときに価値最大化して詰め込むには？といった整数計画問題。

=== ナップサック問題（＃１５）
「容量 C のナップサックが一つと、n 種類の品物（各々、価値 pi, 容積 ci）が与えられたとき、ナップサックの容量 C を超えない範囲でいくつかの品物をナップサックに詰め、ナップサックに入れた品物の価値の和を最大化するにはどの品物を選べばよいか」という整数計画問題。

==== ナップサック問題の応用例
プロジェクトの選択や物資の購入などの問題に応用されている。

====　ナップサック問題のサンプルプログラムとデータ
//listnum[No15][ナップサック問題のサンプルプログラム]{
###Knapsacks

from __future__ import print_function
from ortools.algorithms import pywrapknapsack_solver

def main():
  # Create the solver.
  solver = pywrapknapsack_solver.KnapsackSolver(
      pywrapknapsack_solver.KnapsackSolver.
      KNAPSACK_DYNAMIC_PROGRAMMING_SOLVER,
      'test')

  weights = [[565, 406, 194, 130, 435, 367, 230, 315, 393,
              125, 670, 892, 600, 293, 712, 147, 421, 255]]
  capacities = [850]
  values = weights[0]
  solver.Init(values, weights, capacities)
  computed_value = solver.Solve()

  packed_items = [x for x in range(0, len(weights[0]))
                    if solver.BestSolutionContains(x)]
  packed_weights = [weights[0][i] for i in packed_items]

  print("Packed items: ", packed_items)
  print("Packed weights: ", packed_weights)
  print("Total weight (same as total value): ", computed_value)
if __name__ == '__main__':
  main()
//}

//listnum[No15-2][ナップサック問題の解]{
Packed items:  [2, 3, 6, 13]
Packed weights:  [194, 130, 230, 293]
Total weight (same as total value):  847
//}

=== ビンパッキング問題（＃１６）

==== ピンパッキング問題の応用例
ナップサック問題のナップサックを複数個に拡張した問題

==== ピンパッキング問題のサンプルプログラム
//listnum[No16][ピンパッキング問題のサンプルコード]{
from ortoolpy import binpacking
binpacking(10, [4, 5, 3, 8, 7, 6, 2, 3])　 # ビンのサイズと中に詰める荷物のサイズ
//}

//listnum[No16-2][ピンパッキング問題の解]{
[[8], [7, 3], [5, 3, 2], [4, 6]]
//}


=== ｎ次元詰め込み問題（＃１７）
所与の「荷物（平面上のサイズ[=2次元]がついている）」を詰める「箱（ビンやコンテナなど）」の最小数を見つけるもの。
ビンパッキングが重さ（だけ）とか個数（だけ）とかスカラーなのに対しベクトル（2次元）になる。

//listnum[no17][n次元詰め込み問題のサンプルコード]{
rom ortoolpy import TwoDimPackingClass
  
def TwoDimPacking(df, width, height, width_label='width',
        height_label='height', x_label='x', y_label='y', **kwargs):
    """
    2次元パッキング問題
        ギロチンカットで元板からアイテムを切り出す(近似解法)
    入力
        df: アイテムのDataFrameもしくはCSVファイル名
        width: 元板の横
        height: 元板の縦
        width_label: アイテムの横の属性文字
        height_label: アイテムの縦の属性文字
        x_label: アイテムのX座標の属性文字(結果)
        y_label: アイテムのY座標の属性文字(結果)
    出力
        容積率と入ったアイテムのDataFrame
    """
    df = graph_from_table(df, None, no_graph=True, **kwargs)[1]
    df = df.reset_index(drop=True)
    dt = df[[width_label,height_label]].values
    r,t = TwoDimPackingClass(width, height, dt).solve()
    t = np.array(t)
    df = df.iloc[t[:,0]]
    df[x_label] = t[:,3]
    df[y_label] = t[:,4]
    return r,df
   
TwoDimPackingClass(500, 300, [(240, 150), (260, 100), \
    (100, 200), (240, 150), (160, 200)]).solve()

//}

//listnum[No17-2][n次元詰め込み問題の出力]{
(1.0,
 [(0, 240, 150, 0, 0),
  (1, 260, 100, 240, 0),
  (4, 160, 200, 240, 100),
  (2, 100, 200, 400, 100),
  (3, 240, 150, 0, 150)])
//}

== 配置問題
施設の配置可能地点, 需要をもつ顧客の集合が与えられて, ある基準を満たす施設の配置場所を決定する問題の総称。
=== 施設配置問題（＃１８）
問題の基本形としては, メディアン問題 (median problem), センター問題 (center problem), 容量制約なし施設配置問題 (uncapacitated facility location problem)または単純施設配置問題 (simple facility location problem)が挙げられる. 前者の2つの問題は, 選択される施設の個数があらかじめ決められている場合には, 選択する施設数をpとしてそれぞれ, p-メディアン問題 (p-median problem), p-センター問題 (p-center problem)とよばれる。[Wikipedia]

//listnum[no18][施設配置問題のサンプルコード]{
from ortoolpy import facility_location
　　
def FacilityLocation(df, p, x_label='x', y_label='y', demand_label='demand',
        capacity_label='capacity', result_label='id', func=None, **kwargs):
    """
    施設配置問題
        P-メディアン問題：総距離×量の和の最小化
    入力
        df: ポイントのDataFrameもしくはCSVファイル名
        p: 施設数上限
        x_label: X座標の属性文字
        y_label: Y座標の属性文字
        demand_label: 需要の属性文字(空なら需要なし)
        capacity_label: 容量の属性文字(空なら候補でない)
        result_label: 施設IDの属性文字(結果,利用時はdropna().astype(int))
        func: 顧客位置index,施設候補indexを引数とする重み関数
    出力
        ポイントのDataFrame
    """
    df = graph_from_table(df, None, no_graph=True, **kwargs)[1]
    df = df.reset_index(drop=True)
    df1 = df.dropna(subset=[demand_label])[[x_label,y_label,demand_label]]
    df2 = df.dropna(subset=[capacity_label])[[x_label,y_label,capacity_label]]
    t = facility_location(p, df1.values, df2.values, func=func)
    df.loc[df1.index, result_label] = df2.iloc[t].index
    return df
　　　
facility_location(2, [(1, 0, 1), (0, 1, 1), (2, 2, 1)], 
                     [(1, 0, 1), (0, 1, 1), (2, 2, 2)])
//}

//listnum[no18-2][施設配置問題の出力]{
[0, 2, 2]
//}

=== 容量制約なし施設配置問題（＃１９）
顧客の需要, 顧客と施設の間に1単位の需要が移動するときにかかる輸送費用, 施設を配置するときにかかる固定費用が与えられたとき, すべての顧客の需要を満足するという条件の下で, 輸送費用と固定費用の総和を最小化するような施設の配置ならびに顧客・施設間の輸送量を決定する問題.

==== 容量制約なし施設配置問題の応用例

==== 要領制約なし施設配置問題のサンプルプログラム
//listnum[No19][要領制約なし施設配置問題のサンプルコード]{
from ortoolpy import facility_location_without_capacity
   
def FacilityLocationWithoutCapacity(df, p, x_label='x', y_label='y',
        user_label='demand', facility_label='capacity',
        result_label='id', func=None, **kwargs):
    """
    施設配置問題
        P-メディアン問題：総距離×量の和の最小化
    入力
        df: ポイントのDataFrameもしくはCSVファイル名
        p: 施設数上限
        x_label: X座標の属性文字
        y_label: Y座標の属性文字
        user_label: 空でない場合顧客を表す属性文字
        facility_label: 空でない場合施設を表す属性文字
        result_label: 施設IDの属性文字(結果,利用時はdropna().astype(int))
        func: 顧客位置index,施設候補indexを引数とする重み関数
    出力
        ポイントのDataFrame
    """
    df = graph_from_table(df, None, no_graph=True, **kwargs)[1]
    df = df.reset_index(drop=True)
    df1 = df.dropna(subset=[user_label])[[x_label,y_label]]
    df2 = df.dropna(subset=[facility_label])[[x_label,y_label]]
    t = facility_location_without_capacity(p, df1.values, df2.values, func=func)
    df.loc[df1.index, result_label] = df2.iloc[t].index
    return df
   
    
facility_location_without_capacity(2, [(1, 0), (0, 1), (2, 2)])
//}
//listnum[No18-2][要領制約なし施設配置問題の解]{
[1, 1, 2]
//}

== 割り当て・マッチング問題
=== 二次割り当て問題（＃２０）
目的関数が2次式となる割当問題のこと. 設置予定の工場とその場所候補が与えられており, 工場間の輸送量がq_ik, 場所間の距離がd_jlとするとき, 輸送の量と距離の積の総和を最小化する問題は, P_i を L_j に設置する際に1となる0/1変数 x_ijを導入すると, 割当問題の制約に対して目的関数は2次式 
q_ik * d_jl * x_ij となる。一見3次式に見えるが、x_ijは当該候補地に設置されるときに1,設置されないとき0となるいわばオンオフの変数なので、2次式となる。

==== 二次元割り当て問題の応用例

==== 二次元割り当て問題のサンプルプログラム
//listnum[No20][二次元割り当て問題のサンプルプログラム]{
from ortoolpy import quad_assign
   
def QuadAssign(dfqu, dfdi, from_label='from', to_label='to',
        quant_label='quant', dist_label='dist',
        target_label='target', pos_label='pos', **kwargs):
    """
    2次割当問題
        全探索
    入力
        dfqu: 対象間の輸送量のDataFrameもしくはCSVファイル名
        dfdi: 割当先間の距離のDataFrameもしくはCSVファイル名
        from_label: 輸送元番号の属性文字
        to_label: X輸送先番号の属性文字
        quant_label: 必要輸送量の属性文字
        dist_label: 距離の属性文字
        target_label: 対象の属性文字(結果)
        pos_label: 位置の属性文字(結果)
    出力
        評価値と割当
    """
    dfqu = graph_from_table(dfqu, None, no_graph=True, **kwargs)[1]
    dfdi = graph_from_table(dfdi, None, no_graph=True, **kwargs)[1]
    tmp = dfdi.copy()
    tmp[[to_label,from_label]] = tmp[[from_label,to_label]]
    dfdi = pd.concat([dfdi,tmp]).drop_duplicates([from_label,to_label])
    r = range(max(dfqu[[from_label,to_label]].max().max(),
                  dfdi[[from_label,to_label]].max().max())+1)
    q = [[first(dfqu[(dfqu[from_label]==i)&(dfqu[to_label]==j)]
          [quant_label],0) for j in r] for i in r]
    d = [[first(dfdi[(dfdi[from_label]==i)&(dfdi[to_label]==j)]
          [dist_label],np.inf) for j in r] for i in r]
    r,t = quad_assign(q,d)
    return r, pd.DataFrame([i for i in enumerate(t)], columns=[target_label,pos_label])
    
quad_assign([[0, 2, 0], [0, 0, 1], [0, 0, 0]], [[0, 2, 4], [2, 0, 3], [4, 3, 0]])
//}

//listnum[No20-2][二次元割り当て問題の解]{
(7, (0, 1, 2))
//}

=== 一般化割り当て問題（＃２１）
割当問題を拡張した問題。通常の機械と仕事との割り当てに加えて, 機械iが仕事jを行ったときの負荷a_ijを考える. また, 機械iには能力の制限b_iがあるとする。のとき, 割当問題の制約式は、一方が各機械毎にa_ij * x_ij <= b_iの合計のような制約に置換えられる. 通常の割当問題とは異なり, 左辺係数行列に負荷a_ijの係数が関わるため, 全ユニモジュラ性が失われ, NP困難な問題となる. 実行可能解の存否を判定するだけでもNP完全な問題である。[Wikipedia]

==== 一般化割り当て問題の応用例

==== 一般化割り当て問題のサンプルプログラム
//listnum[No21][一般化割り当て問題のサンプルプログラム]{
from ortoolpy import gap
 
def Gap(df, capacity, agent_label='agent', job_label='job',
        cost_label='cost', req_label='req', **kwargs):
    """
    一般化割当問題
        費用最小の割当を解く
    入力
        df: DataFrameもしくはCSVファイル名
        capacity: エージェントの容量のリスト
        agent_label: エージェントの属性文字
        job_label: ジョブの属性文字
        cost_label: 費用の属性文字
        req_label: 要求量の属性文字
    出力
        選択されたDataFrame
    """
    df = graph_from_table(df, None, no_graph=True, **kwargs)[1]
    a = range(df[agent_label].max()+1)
    j = range(df[job_label].max()+1)
    c = [[first(df[(df[agent_label]==i)&(df[job_label]==k)]
          [cost_label],0) for k in j] for i in a]
    r = [[first(df[(df[agent_label]==i)&(df[job_label]==k)]
          [req_label],1e6) for k in j] for i in a]
    t = gap(c, r, capacity)
    return pd.concat([df[(df[agent_label]==i)&(df[job_label]==k)]
        for k,i in enumerate(t)])
  
gap([[2, 2, 2], [1, 1, 1]], [[1, 1, 1], [1, 1, 1]], [2, 1])
//}

//listnum[no21-2][一般化割り当て問題の解]{
[0,0,1]
//}

=== 最大マッチング問題（＃２２）
グラフが与えられたときに要素数最大のマッチングを求める問題を最大マッチング問題と言う。
辺からなる集合のうち、どの2辺も端点を共有しないようなものをマッチングと呼び、最大サイズのマッチングを求める問題。

//image[image17][最大マッチングの一例][scale=0.5]

赤太線で示した 2 本の辺集合が最大マッチングの一例。 3 本とれそうですがとれない。応用例
左側の頂点を「男性」，右側の頂点を「女性」とする2部グラフに於いて、「お互い付き合ってもよいペア」に枝を引いたグラフを考え，カップル成立のペア数を最大化する問題。

//image[image18][仕事割り当て問題の例][scale=0.5]

2部の「部」の分けを労働者と業務とすれば、仕事割当問題になる。

==== 最大マッチング問題のサンプルプログラム
//listnum[No22][最大マッチング問題のサンプルプログラム]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw
  
def MaxMatching(dfed, from_label='node1', to_label='node2', **kwargs):
    """
    最大マッチング問題
    入力
        dfed: 辺のDataFrameもしくはCSVファイル名
        from_label: 元点の属性文字
        to_label: 先点の属性文字
    出力
        選択された辺のDataFrame
    """
    return MaxWeightMatching(dfed, from_label=from_label,
        to_label=to_label, weight_label='', **kwargs)
      
# CSVデータ
tbn = pd.read_csv('./node0.csv')
tbe = pd.read_csv('./edge0.csv')
g = graph_from_table(tbn, tbe)[0]
for i, j in g.edges():
    del g.adj[i][j]['weight']
d = nx.max_weight_matching(g)
pos = networkx_draw(g)
nx.draw_networkx_edges(g, pos, width=3, edgelist=[(i, j) for i, j in d])
plt.show()
print(d)
//}

//image[image][最大マッチング問題の解]

=== 最大重みマッチング問題（＃２３）
無向グラフに対し、各辺の重みが与えられているときに重みの和が最大となるマッチングを求める問題。

マッチング：どの2辺も端点を共有しないような状態。

==== 最大重みマッチング問題の応用例

労働者と業務をグラフ上の頂点として、それらを結びつける辺の重みを利益とする場合に総利益を最大化する業務割当など。

//image[image20][最大重みマッチング問題のイメージ]

==== 最大重みマッチング問題のサンプルプログラムとデータ

//listnum[code20][重みマッチング問題のサンプルプログラム]{
import pandas as pd, networkx as nx, matplotlib.pyplot as plt
from ortoolpy import graph_from_table, networkx_draw
     
def MaxWeightMatching(dfed, from_label='node1', to_label='node2',
        weight_label='weight', **kwargs):
    """
    最大重みマッチング問題
    入力
        dfed: 辺のDataFrameもしくはCSVファイル名
        from_label: 元点の属性文字
        to_label: 先点の属性文字
        weight_label: 辺の重みの属性文字
    出力
        選択された辺のDataFrame
    """
    g,_,dfed = graph_from_table(None, dfed, from_label=from_label,
        to_label=to_label, from_to='FrTo_', **kwargs)
    for i, j in g.edges():
        g.adj[i][j]['weight'] = g.adj[i][j].get(weight_label,1)
    t =  nx.max_weight_matching(g)
    dftmp = pd.DataFrame(['{min(i,j)}-{max(i,j)}'
        for i,j in t.items() if i < j], columns=['FrTo_'])
    return pd.merge(dfed, dftmp).drop('FrTo_',1)
 
    
tbn = pd.read_csv('./node0.csv')
tbe = pd.read_csv('./edge0.csv')
g = graph_from_table(tbn, tbe)[0]
d = nx.max_weight_matching(g)
pos = networkx_draw(g)
nx.draw_networkx_edges(g, pos, width=3, edgelist=[(i, j) for i, j in d])
plt.show()
print(d)
//}

//image[image21][最大重みマッチング問題の解][scale=0.5]

//listnum[No20-2][最大重みマッチング問題の解]{
{(1, 5), (3, 4), (0, 2)}
//}

=== 安定マッチング問題（＃２４）
2部グラフにおいては、各部に属する頂点群が相対する部の頂点群に対する嗜好順位を有する状況下で、マッチングを行う場合に、そのマッチングを崩して別のマッチングを組んだほうがその頂点にとりより高い嗜好順位とのマッチングにならない状態（個人合理性を満たす）を求める問題。

==== 安定マッチング問題の応用例

研修医の配属問題、研究室への配属問題
ねるとん紅鯨団

==== 安定マッチング問題のサンプルプログラムとデータ

//listnum[code24][重みマッチング問題のサンプルプログラム]{
from ortoolpy import stable_matching
import numpy as np, pandas as pd, networkx as nx
import IPython.core.getipython
from IPython.display import HTML
from more_itertools import first, pairwise
  
def typical_optimization_impl(sel):
    return HTML("""\
<table>
  <td><a href="http://qiita.com/SaitoTsutomu/items/2ec5f7626054f4b4de63" target="_blank">安定マッチング問題</a></td>
  <td>StableMatching</td>
</tr>
</table>
""")
  
def StableMatching(df, male_label='male', female_label='female',
        pref_male_label='pref_male', pref_female_label='pref_female', **kwargs):
    """
    安定マッチング問題
    入力
        df: 選好のDataFrameもしくはCSVファイル名
        male_label: 男性の属性文字
        female_label: 女性の属性文字
        pref_male_label: 男性から見た順番の属性文字
        pref_female_label: 女性から見た順番の属性文字
    出力
        マッチングのDataFrame(男性優先)
    """
    df = graph_from_table(df, None, no_graph=True, **kwargs)[1]
    m = range(df[male_label].max()+1)
    f = range(df[female_label].max()+1)
    prefm = [[first(df[(df[male_label]==i)&(df[pref_male_label]==j)]
             [female_label],1e6) for j in f] for i in m]
    preff = [[first(df[(df[female_label]==i)&(df[pref_female_label]==j)]
             [male_label],1e6) for j in m] for i in f]
    t = stable_matching(prefm, preff)
    return pd.concat([df[(df[female_label]==i)&(df[male_label]==j)]
        for i,j in t.items()]).sort_values(male_label)
 
if __name__ == '__main__':
    ip = IPython.core.getipython.get_ipython()
    ip.register_magic_function(typical_optimization_impl,
        magic_kind='line', magic_name='typical_optimization')
     
print(stable_matching([[2,0,1],[2,1,0],[0,2,1]], [[0,1,2],[2,0,1],[2,1,0]]))
//}

//listnum[No24][安定マッチング問題の解]{
{0: 0, 1: 1, 2: 2}
//}

== まとめ

早速倉庫の業務、顧客注文に応じて出荷用に棚から物を取ってくる作業時の動線短縮・合理化のお題がでたので巡回セールスマン辺りを深堀中です。サンプルではユークリッドの直線距離だけど、倉庫で隣の棚に行くには通路を回り込まないとってところです。
今後は、こういたカタログのExcel版を作れれば、Excelならなんとかという方々にも数理最適化が布教できるのではないかと思量。
