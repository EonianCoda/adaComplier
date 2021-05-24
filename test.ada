program test
    declare 
        a: integer ;
        b: integer ;
    procedure apple
        declare
            p: integer;
        begin
            for (p in 5 .. 6) loop
                print a;
            end loop;
        end;
    end apple;
    begin
        apple();
    end
end test