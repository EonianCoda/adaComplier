program test
    declare 
        a: integer ;
        b: integer ;
    procedure apple return float
        declare
            p: integer;
        begin
            for (p in 5 .. 6) loop
                print a;
            end loop;
        end;
    end apple;
    procedure bpple(a: integer; b: float) return integer
        declare
            p: integer;
        begin
            for (p in 5 .. 6) loop
                print a;
            end loop;
            return;
        end;

    end bpple;
    begin
        a := apple() + bpple(1.0, 5);
    end
end test