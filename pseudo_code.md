semaphore mutex = 1;
semaphore fillCount = 0;
semaphore emptyCount = BUFFER_SIZE;

procedure producer() {
    while (true) {
        item = produceItem();
        down(emptyCount);
            down(mutex);
                putItemIntoBuffer(item);
            up(mutex);
        up(fillCount);
    }
}

procedure consumer() {
    while (true) {
        down(fillCount);
            down(mutex);
                item = removeItemFromBuffer();
            up(mutex);
        up(emptyCount);
        consumeItem(item);
    }
}


Using a condition variable and a mutex[edit]
Alternatively, a read-preferring R/W lock can be implemented in terms of a condition variable and an ordinary (mutex) lock, in addition to an integer counter and a boolean flag. The lock-for-read operation in this setup is:[6][7][8]

Input: mutex m, condition variable c, integer r (number of readers waiting), flag w (writer waiting).
Lock m (blocking).
While w:
wait c, m[a]
Increment r.
Unlock m.
The lock-for-write operation is similar, but slightly different (inputs are the same as for lock-for-read):[6][7][8]

Lock m (blocking).
While (w or r > 0):
wait c, m
Set w to true.
Unlock m.

