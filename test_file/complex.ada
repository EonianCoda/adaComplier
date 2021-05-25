program test
    declare
      a: integer;
      b: integer := 10;
      c: constant : integer := 10;
      d: string := "absd";
      z: float := 0.2;
      x: integer [20];
    procedure test () return integer
      declare
          p: integer;
        begin
          for ( p in 2 . . 5) loop
          begin
              print(p);
            end;
          end loop;
          p := 1;
          return p;
        end;
      end test;
    procedure add (e: integer; h: float; u: string) return integer
      declare
        p: integer;
      begin
        for ( p in 2 . . 5) loop
        begin
            print(a);
          end;
        end loop;
        return e+1;
      end;
    end add;
    begin
      a := b + 1;
      a := b + x[5];
      a := b + c * x[7];
      a := add(b ,z , d);
      print(b+c);
      println(b+c);

      -- test if
      if a > 1 then
        begin
          print(a);
        end;
      end if;

      -- test for
      for ( a in 2 . . 5) loop
        begin
          print(a);
        end;
      end loop;

      -- test while
      while  a > 1 loop
        begin
          print(a);
        end;
      end loop;

    end
end test