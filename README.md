# grp [![NPM version](https://badge.fury.io/js/grp.svg)](http://badge.fury.io/js/grp)
> &lt;grp.h&gt; binding for [node](http://nodejs.org).



```js
var fs = require('fs');
var grp = require('grp');

var stat = fs.statSync(path);

var group = grp.getgrgid(stat.gid);
console.log('the group name for "' + path + '" is: ' + group.gr_name);
```
## Installation

```sh
$ npm install grp --save
```    

## Features

There is two available functions:

+ getgrgid(gid)
```js
    var group = grp.getgrgid(10);
```
+ getgrnam(name)
```js
    var group = grp.getgrnam('wheel');
```

These functions obtain information from opendirectoryd(8), including records in /etc/group which is described in group(5).
Each line of the database is defined by the structure group like found in the include file &lt;grp.h&gt;:

```js
{
    gr_name        /* group name */
    gr_passwd,     /* group password - NOT SUPPORTED IN V1.0.0 */
    gr_gid,        /* group id */
    gr_mem         /* group members - NOT SUPPORTED IN V1.0.0 */
}
```

## More Information

```sh
$ man 3 getgrgid
```
## License

MIT
