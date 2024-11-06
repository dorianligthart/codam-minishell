### getline():
- if (newline in saved[fd]) return split();
- read on top of saved[fd] until newline or EOF;
- if (newline in saved[fd]) return split();
- else *line = saved[fd]; saved[fd] = NULL; return bytesread;

### main():
```
mstruct ms;
ssize_t ret;
while (1)
{
    ret = getline();
    if (ret < 0) break;
    ret = parse_line();
    if (ret < 0) break;
}
return (cleaner_function(ret));
 ```
