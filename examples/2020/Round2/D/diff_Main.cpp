diff --git a/CodeJam/Main.cpp b/examples/2020/Round2/D/Main.cpp
index e858c1d..fc5fb4c 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round2/D/Main.cpp
@@ -1012,11 +1012,271 @@ namespace task {
 void init(){
 }
 
+v(ll) compute_Pj(const str& P){
+    llog("called compute_Pj");
+    v(ll) ans(P.sz, -1);
+    stack<ll, v(ll)> st;
+    forn(i, P.sz){
+        if(P[i]=='(') st.push(i);
+        else{
+            lassert(P[i]==')', "not open or closing bracket here");
+            ll match = st.top();
+            st.pop();
+            ans[match]=i;
+            ans[i]=match;
+        }
+    }
+    lassert(st.empty(), "stack is not empty here");
+    llog("P", P);
+    llog("Pj", ans);
+    return ans;
+}
+
+p(ll, ll) get_mid_bracket(const p(ll, ll)& outer, const v(ll)& Pj){
+    llog("called get_mid_bracket");
+    ll mid2 = outer.st + outer.nd;
+    fore(i, outer.st+1, outer.nd-1){
+        ll m = Pj[i];
+        if(m<=i) continue;
+        if(mid2<2*m){
+            llog(Pj);
+            llog(i, m);
+            return mp(i, m);
+        }
+        i=m;
+    }
+    lassert(false, "how did we come here?");
+}
+
+v(ll) get_quadruple_split(const v(ll)& Pj){
+    p(ll, ll) outer = mp(-1, Pj.sz);
+    p(ll, ll) inner = get_mid_bracket(outer, Pj);
+    while(inner.nd - inner.st >= Pj.sz/2){
+        outer = inner;
+        inner = get_mid_bracket(outer, Pj);
+    }
+    v(ll) ans;
+    ans.pb(outer.st);
+    ans.pb(inner.st);
+    ans.pb(inner.nd);
+    ans.pb(outer.nd);
+    return ans;
+}
+
+ll K, Q;
+str P;
+v(ll) Li, Ri, Pi, Sj, Ej;
+
+v(ll) dijkstra(const ll start, const v(ll)& Pj, const v(ll)& Li, const v(ll)& Ri, const v(ll)& Pi, const bool outward){
+    v(ll) ans(Pj.sz, INF);
+    priority_queue<p(ll,ll), v(p(ll,ll)) , greater<p(ll,ll)> > pq;
+    v(bool) visited(Pj.sz, false);
+    ans[start] = 0;
+    // visited[start] = true;
+    pq.push(mp(0, start));
+    while(!pq.empty()){
+        ll node = pq.top().second;
+        pq.pop();
+        if(visited[node]) continue;
+
+        v(p(ll, ll)) neighs;
+        if(outward){
+            if(node > 0)
+                neighs.pb(mp(node-1, Li[node]));
+            if(node +1 < Pj.sz)
+                neighs.pb(mp(node+1, Ri[node]));
+            neighs.pb(mp(Pj[node], Pi[node]));
+        }
+        else{
+            if(node > 0)
+                neighs.pb(mp(node-1, Ri[node-1]));
+            if(node +1 < Pj.sz)
+                neighs.pb(mp(node+1, Li[node+1]));
+            neighs.pb(mp(Pj[node], Pi[Pj[node]]));
+        }
+
+        lassert(ans[node] < INF, "visited node has distance INF");
+        for (auto x : neighs){
+            ll neigh_node = x.first;
+            ll edge_dist = x.second;
+            if(edge_dist == INF) continue;
+            if (ans[neigh_node] == INF || ans[neigh_node] > ans[node] + edge_dist){
+                ans[neigh_node] = ans[node] + edge_dist;
+                pq.push(mp(ans[neigh_node], neigh_node));
+            }
+        }
+        visited[node] = true;
+    }
+    return ans;
+}
+
+ll get_slot_id(const ll& idx, const v(ll)& split_locs){
+    lassert(split_locs.sz==4, "this code works only with correct split locs size");
+    ll ans = -1;
+    if(idx<split_locs[0] || idx > split_locs[3]) ans=0;
+    if(idx>split_locs[0] && idx < split_locs[1]) ans=1;
+    if(idx>split_locs[1] && idx < split_locs[2]) ans=2;
+    if(idx>split_locs[2] && idx < split_locs[3]) ans=3;
+    return ans;
+}
+
+v(ll) recur(const str& P, const v(ll)& Li, const v(ll)& Ri, const v(ll)& Pi, const v(ll)& Sj, const v(ll)& Ej){
+    llog("cur recur on", P);
+    llog("costs Li, Ri, Pi");
+    llog(Li);
+    llog(Ri);
+    llog(Pi);
+    llog("queries");
+    llog(Sj);
+    llog(Ej);
+    v(ll) ans;
+    if(Sj.sz == 0) return ans;
+    v(ll) Pj = compute_Pj(P);
+    if(P.sz <= 4){
+        forn(i, Sj.sz){
+            ans.pb(dijkstra(Sj[i], Pj, Li, Ri, Pi, true)[Ej[i]]);
+        }
+        llog("result");
+        llog(ans);
+        return ans;
+    }
+    ans.assign(Sj.sz, INF);
+
+    v(ll) split_locs = get_quadruple_split(Pj);
+    lassert(split_locs.sz == 4, "why are there not 4 split locs");
+
+    forn(sid, 4){
+        if(split_locs[sid] < 0 || split_locs[sid] >= Pj.sz) continue;
+        v(ll) to_sloc = dijkstra(split_locs[sid], Pj, Li, Ri, Pi, false);
+        llog("dijkstra to loc", split_locs[sid]);
+        llog(to_sloc);
+        v(ll) from_sloc = dijkstra(split_locs[sid], Pj, Li, Ri, Pi, true);
+        llog("dijkstra from loc", split_locs[sid]);
+        llog(from_sloc);
+        forn(i, Sj.sz){
+            if(to_sloc[Sj[i]] == INF) continue;
+            if(from_sloc[Ej[i]] == INF) continue;
+            lassert(to_sloc[Sj[i]] != INF, "why is there inf here");
+            lassert(from_sloc[Ej[i]] != INF, "why is there inf here");
+            ans[i] = min<ll>(ans[i], to_sloc[Sj[i]] + from_sloc[Ej[i]]);
+        }
+    }
+
+    v(v(ll)) query_ids(4);
+    v(p(ll,ll)) query_slots;
+    forn(i, Sj.sz){
+        ll s = get_slot_id(Sj[i], split_locs);
+        ll e = get_slot_id(Ej[i], split_locs);
+        llog("found query", Sj[i], Ej[i]);
+        llog("slot locations are", s, e);
+        if(s==e && s!=-1){
+            query_ids[s].pb(i);
+        }
+    }
+
+    llog("split locs", split_locs);
+    forn(sub, 4){
+        if(query_ids[sub].sz == 0) continue;
+        if(sub==0){
+            if(split_locs[0]==-1){
+                lassert(false, "should be handled by checking there are no queries for this case");
+                lassert(split_locs[3] == P.sz, "empty outer block but something is wrong");
+                continue;
+            }
+        }
+        llog("sub", sub);
+        str subP;
+        if(sub==0){
+            subP = P.substr(0, split_locs[0]) + P.substr(split_locs[3]+1);
+        } else {
+            subP = P.substr(split_locs[sub-1]+1, split_locs[sub]-split_locs[sub-1]-1);
+        }
+        llog("subP", subP);
+
+        v(ll) subLi, subRi, subPi;
+        if(sub==0){
+            subLi.insert(subLi.bn, msel(Li, 0, split_locs[0]));
+            subRi.insert(subRi.bn, msel(Ri, 0, split_locs[0]));
+            if(split_locs[0]>0) subRi.bk = INF;
+            subPi.insert(subPi.bn, msel(Pi, 0, split_locs[0]));
+            subLi.insert(subLi.ed, msel(Li, split_locs[3]+1, Li.sz));
+            subLi[split_locs[0]] = INF;
+            subRi.insert(subRi.ed, msel(Ri, split_locs[3]+1, Ri.sz));
+            subPi.insert(subPi.ed, msel(Pi, split_locs[3]+1, Pi.sz));
+        } else {
+            subLi.insert(subLi.bn, msel(Li, split_locs[sub-1]+1, split_locs[sub]));
+            subRi.insert(subRi.bn, msel(Ri, split_locs[sub-1]+1, split_locs[sub]));
+            subPi.insert(subPi.bn, msel(Pi, split_locs[sub-1]+1, split_locs[sub]));
+        }
+        llog("subLi", subLi);
+
+        v(ll) subSj, subEj;
+        if(sub==0){
+            forn(i, query_ids[sub].sz){
+                ll s = Sj[query_ids[sub][i]];
+                ll e = Ej[query_ids[sub][i]];
+                s = s < split_locs[0] ? s : s - split_locs[3] + split_locs[0]-1;
+                e = e < split_locs[0] ? e : e - split_locs[3] + split_locs[0]-1;
+                subSj.pb(s);
+                subEj.pb(e);
+            }
+        } else {
+            forn(i, query_ids[sub].sz){
+                ll s = Sj[query_ids[sub][i]] - split_locs[sub-1] - 1;
+                ll e = Ej[query_ids[sub][i]] - split_locs[sub-1] - 1;
+                subSj.pb(s);
+                subEj.pb(e);
+            }
+        }
+
+        v(ll) recur_ans = recur(subP, subLi, subRi, subPi, subSj, subEj);
+        forn(i, recur_ans.sz){
+            ans[query_ids[sub][i]] = min(ans[query_ids[sub][i]], recur_ans[i]);
+        }
+    }
+
+    llog("result");
+    llog(ans);
+    return ans;
+}
+
+
+
 void readInput(){
+    cin >> K >> Q;
+    cin >> P;
+    Li.resize(K);
+    Ri.resize(K);
+    Pi.resize(K);
+    Sj.resize(Q);
+    Ej.resize(Q);
+    forn(i, K) cin >> Li[i];
+    forn(i, K) cin >> Ri[i];
+    forn(i, K) cin >> Pi[i];
+    forn(i, Q) cin >> Sj[i];
+    forn(i, Q) cin >> Ej[i];
+    forn(i, Q) Sj[i]--;
+    forn(i, Q) Ej[i]--;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+
+    // // brute force solution
+    // v(ll) query_results(Q, INF);
+    // forn(i, Q){
+    //     v(ll) cur_dijkstra = dijkstra(Ej[i], compute_Pj(P), Li, Ri, Pi, false);
+    //     // llog(cur_dijkstra[Ej[i]]);
+    //     query_results[i] = cur_dijkstra[Sj[i]];
+    // }
+
+    // smart solution
+    v(ll) query_results = recur(P, Li, Ri, Pi, Sj, Ej);
+
+    llog("query results");
+    llog(query_results);
+    forn(i, Q) result += query_results[i];
 }
 
 } // namespace task
