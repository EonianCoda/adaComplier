program test
  declare
    global_int : integer;
    global_float : float;
  --void procedure
  procedure a () 
    begin
    end;
  end a;
  --int function
  procedure b return integer
    begin
      return 1;
    end;
  end b;
  --args void procedure
  procedure c (g : float) 
    begin
      read g;
    end;
  end c;
  --main block
  begin
    a();
    b();
    c(3.0);
    global_int := (b(b()) + 9)*10;
    global_float := (c(2.0) + 6.0);
  end;
end test
