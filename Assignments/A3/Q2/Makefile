CC=gcc

P1fifo: P1fifo.c
	@$(CC) P1fifo.c -o P1fifo
	
P2fifo: P2fifo.c
	@$(CC) P2fifo.c -o P2fifo
	
P1soc: P1soc.c
	@$(CC) P1soc.c -o P1soc
	
P2soc: P2soc.c
	@$(CC) P2soc.c -o P2soc
	
P1mq: P1mq.c
	@$(CC) P1mq.c -o P1mq -lrt
	
P2mq: P2mq.c
	@$(CC) P2mq.c -o P2mq -lrt

clean:
	@rm -f P1fifo P2fifo P1soc P2soc P1mq P2mq