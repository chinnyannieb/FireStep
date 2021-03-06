# FireStep

FireStep is an Arduino stepper library for FirePick Delta.
FireStep responds to 
[JSON requests](https://github.com/firepick1/FireStep/wiki/JSON-Reference)
written in a flexible
[query-by-example](https://github.com/firepick1/FireStep/wiki/JSON-Query-by-Example)
interaction style inspired by [TinyG](https://github.com/synthetos/TinyG/wiki/JSON-Operation).

* [JSON-Query-by-Example](https://github.com/firepick1/FireStep/wiki/JSON-Query-by-Example)
* [JSON-Reference](https://github.com/firepick1/FireStep/wiki/JSON-Reference)

FireStep is designed to work with Pythagorean Hodograph Quintic Curves (PH5Curve), which 
are smooth, polynomial paths defined by on-path control points. FireStep also
implements PHFeed, which controls feed acceleration continuously during path traversal, 
providing smooth motion.

* [PH5Curve Stepper Video](https://www.youtube.com/watch?v=iFprR51CGqE)

