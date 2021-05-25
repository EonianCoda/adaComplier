program test
    declare
        --by value
        a := 10;
        b := 10.0;
        c := "str";
        d := false;
        --by type
        e : integer;
        f : float;
        g : string;
        h : boolean;
        --by value and type
        i : integer := 5;
        j : float := 10.0;
        k : string := "str";
        l : boolean := true;
        --multiple declare
        m, n := 10;
        o, p : string;
        q, r : float := 10.0;
        s, t, u, v : constant := "string"; 
        y : integer[10];
        w : string;
    begin
    end
end test