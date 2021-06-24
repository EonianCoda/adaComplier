program example
    declare
        a :constant := 5;
        c : integer := 123;
        s :constant := "string";
    procedure add (a: integer; b: integer) return integer
        begin
            return a+ b;
        end;
    end add;
    begin
        c := add(a, 10);
        if (c > 10) then 
            print -c; 
        else 
            print c; 
        end if;
        println (s);
        println ("Hello World"); 
    end;
end example