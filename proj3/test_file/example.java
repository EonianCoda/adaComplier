class example
{
    field static int c
    method public static int add(int, int)
    max_stack 15
    max_locals 15
    {
        iload 0
        iload 1
        iadd
        ireturn
    }
    method public static void main(java.lang.String[])
    max_stack 15
    max_locals 15
    {
        sipush 5
        sipush 10
        invokestatic int example.add(int, int)
        putstatic int example.c
        getstatic int example.c
        sipush 10
        isub
        ifgt L0
        iconst_0
        goto L1
        L0:
            iconst_1
        L1:
            ifeq L2
        getstatic java.io.PrintStream java.lang.System.out
        getstatic int example.c
        ineg
        invokevirtual void java.io.PrintStream.print(int)
        goto L3
        L2:
            getstatic java.io.PrintStream java.lang.System.out
        getstatic int example.c
        invokevirtual void java.io.PrintStream.print(int)
        L3:
            getstatic java.io.PrintStream java.lang.System.out
        ldc "Hello World"
        invokevirtual void java.io.PrintStream.println(java.lang.String)

        return
    }
}
