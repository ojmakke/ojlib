.PHONY: clean


test clean:
	$(MAKE) -C ojstack/ $@
	$(MAKE) -C ojmemory/ $@
	$(MAKE) -C ojtimer/ $@
	$(MAKE) -C ojllist/ $@
	$(MAKE) -C ojhash/ $@
 
