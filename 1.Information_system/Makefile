target=infor
obj=$(patsubst %.c,%.o,$(wildcard *.c)) 
cc=gcc

$(target):$(obj)
	$(cc) -o $(target) $^

%.o:%.c
	$(cc) -o $@ -c $<

PHONY:clean
clean:
	rm *.o $(target)
