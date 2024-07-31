fun factorial n =
    if n <= 1 then
      1
    else
      factorial (n-1) * n;
    ;
val cube : real -> real = fn(x) => x*x*x;

val rec pow: int -> int = 
    fn(x) =>
        if x <= 0 then 1
        else 2*pow(x-1);

val rec pow2 : int * int -> int = 
    fn(x,y) =>
        if y <= 0 then 1
        else x*pow2(x,y-1);
        
val rec search : int list * int -> bool =
    fn (lst, n) =>
        if null lst then false
        else if hd lst = n then true
        else search (tl lst, n);
        
val rec sumLists: int list*int list-> int list = 
    fn(l1,l2) => 
        if null l1 orelse null l2 then nil
        else [hd l1 + hd l2] @ sumLists(tl l1, tl l2);
        
    
val rec max:int list -> int = 
    fn [] => raise Empty
    | [x] => x
    | x::xs =>
        let 
            val maxTail = max xs
        in 
            if x > maxTail then x else maxTail
        end;

val rec allTrue: bool list -> bool = 
    fn [] => true
     | lst => hd lst andalso allTrue (tl lst);
     
val rec split: int list -> int list * int list = 
    fn [] => (nil,nil)
    | [x] => ([x],nil)
    | a::b::xs =>
        let 
            val (c,d) = split xs
        in
            ([a]@c, [b]@d)
        end;
split ([1,2,3,4,5])