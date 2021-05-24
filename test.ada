program test
    declare 
        a: integer ;
    procedure add() return integer
        declare 
            d : integer[10];
        begin
            while (TRUE) loop
                begin
                    a := 5;
                end
            end loop;
            print a;
            println a;
            a := 5;
            while (TRUE) loop
                begin
                    a := 5;
                end
            end loop;
            for ( a in 0 .. 5 ) loop
                begin
                    print a;
                end
            end loop ;
        end
    end add;
    begin

    end
end test