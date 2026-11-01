# Changelog

## [2.0.2](https://github.com/airone01/ft/compare/b-v2.0.1...b-v2.0.2) (2026-11-01)


### Bug Fixes

* **b:** correct binary name when version flag ([4284ecb](https://github.com/airone01/ft/commit/4284ecb6ca65d03a55cf678156e271c1d5fbae8b))
* **b:** exit return status ([ae8d8bc](https://github.com/airone01/ft/commit/ae8d8bc812b2baac79b41c4a22dd3589b631fc0c))
* **b:** globals polluting search tree ([99784d9](https://github.com/airone01/ft/commit/99784d9422c8c911984ad8e834fac13f6ea64a09))
* **b:** mistook binary subtraction for unary negation ([63b2a16](https://github.com/airone01/ft/commit/63b2a166e0d086ed3d4eed8a4f654c1c9a7e907c))
* **b:** strtol misuse when parsing octal literals ([a3eea46](https://github.com/airone01/ft/commit/a3eea4677e55fcc5618d681fa813c7eed93aaf88))

## [2.0.1](https://github.com/airone01/ft/compare/b-v2.0.0...b-v2.0.1) (2026-11-01)


### Bug Fixes

* **b:** reverse stack on func call so that args are in ltr order ([4abe523](https://github.com/airone01/ft/commit/4abe52300cf8224cb4d70abc5cf9b34229f810f1))

## [2.0.0](https://github.com/airone01/ft/compare/b-v1.1.0...b-v2.0.0) (2026-11-01)


### ⚠ BREAKING CHANGES

* **b:** move code generation out of the grammar

### Code Refactoring

* **b:** move code generation out of the grammar ([e92ee4d](https://github.com/airone01/ft/commit/e92ee4dca8582c4f1fe10eae0b067217d3442558))

## [1.1.0](https://github.com/airone01/ft/compare/b-v1.0.0...b-v1.1.0) (2026-11-01)


### Features

* **b:** intense testing ([e7a52b1](https://github.com/airone01/ft/commit/e7a52b191eba06be6e4526822afc0671ed558874))
* **b:** options parsing and version display ([4511c1b](https://github.com/airone01/ft/commit/4511c1bb5baea635320c08a68b4f67957872957f))
* **b:** test suite ([e994360](https://github.com/airone01/ft/commit/e994360fb5922e992f0ff6698dc43544b83cc017))

## 1.0.0 (2026-10-21)


### ⚠ BREAKING CHANGES

* mark beaking changes

### Features

* b ([c024f16](https://github.com/airone01/ft/commit/c024f169756e250e78a64cff260dce1c879d41bb))
* **b:** 'break' support in loops ([f38fdc0](https://github.com/airone01/ft/commit/f38fdc0143a0039d0ba9250cd4fb95646b9fd673))
* **b:** address-of, dereference ([a37f360](https://github.com/airone01/ft/commit/a37f36076a95e9693bb87f3008247f52767e9642))
* **b:** array access ([aec30c8](https://github.com/airone01/ft/commit/aec30c8ce0a532dd6d3760a1025856e68032e6c1))
* **b:** assignment in expression ([b4e1b13](https://github.com/airone01/ft/commit/b4e1b13d98409fb9d64de7a74315b12d063fc17c))
* **b:** better errors ([cebab3e](https://github.com/airone01/ft/commit/cebab3e18538ee63335628e0044a5d72d71ddf37))
* **b:** color ([4858385](https://github.com/airone01/ft/commit/4858385b2810d45a6245d250cf876b0250e305d1))
* **b:** compiler optimizations ([75a82cb](https://github.com/airone01/ft/commit/75a82cb7a280d382876158255120e08d633033a1))
* **b:** ctime ([a6c6514](https://github.com/airone01/ft/commit/a6c651490321de855efdf45d60fc17c1fc18e8fd))
* **b:** else ([695700f](https://github.com/airone01/ft/commit/695700f4512b27b5438dbc91e694f376ee47270f))
* **b:** float implementation ([334b1b5](https://github.com/airone01/ft/commit/334b1b5118340fbb9b719dc30df0e29285bc417a))
* **b:** function calls ([9418cea](https://github.com/airone01/ft/commit/9418ceae3d52d3f675d8f15b915c20b6ab1592ed))
* **b:** global vectors and variables ([ce30d11](https://github.com/airone01/ft/commit/ce30d11aaad85b27b714d3e15093c7c2148ed9f2))
* **b:** goto ([d76d110](https://github.com/airone01/ft/commit/d76d110ceedf14a0d75a1630aa6efbab3e5b4faa))
* **b:** if statement, but its broken ([4dbd177](https://github.com/airone01/ft/commit/4dbd1778f2f12cba9eaa5184d9f810787e485416))
* **b:** left and right value ([2d683b3](https://github.com/airone01/ft/commit/2d683b3424a44686ef93833b20145afd4fa67cb7))
* **b:** lexer char support ([49c2360](https://github.com/airone01/ft/commit/49c23607d6eb65d324602e822d7839d3fc9c16cf))
* **b:** libb init ([02b039e](https://github.com/airone01/ft/commit/02b039e5d4ed9b026208f55ba19f50ddafaa40f9))
* **b:** libb syscall wrappers ([df153e7](https://github.com/airone01/ft/commit/df153e773fff0b9c82d73763d2580d24e781a3fb))
* **b:** math expressions ([87224c7](https://github.com/airone01/ft/commit/87224c77a50bc4d09c4f8115d222356a7a88cb18))
* **b:** memory management ([5b0a167](https://github.com/airone01/ft/commit/5b0a1675e0a0853bde40b7cb35980aef24c7391a))
* **b:** more complete lexer syntax ([e1cb7b8](https://github.com/airone01/ft/commit/e1cb7b844dea14cadf9f0fcd1d6bf54149bc707b))
* **b:** new operators ([ac49b8a](https://github.com/airone01/ft/commit/ac49b8aa2f559d8906bc619daffc3310c679f18d))
* **b:** pre/post in/decrement ([4d6b8bd](https://github.com/airone01/ft/commit/4d6b8bd5bbeea6893ed277489fc45e854f0127fd))
* **b:** prettier errors, rm requirement on 'break' for ctime ([f93af70](https://github.com/airone01/ft/commit/f93af709f06a3508a0deccac4c750dece9eba518))
* **b:** printn, printf ([0c9a9f0](https://github.com/airone01/ft/commit/0c9a9f0e96bb3b6a819527b4f53126dc9fd20b0d))
* **b:** return statement, expr in parenthesis ([96fc59d](https://github.com/airone01/ft/commit/96fc59dee5c4c78369f6ea12faee4339e1dbca3d))
* **b:** short-circuit logical `and` and `or` ([9b2bccc](https://github.com/airone01/ft/commit/9b2bccc4e1a0ac66071ac88a93680c0af9974357))
* **b:** subject blobs ([d9a8e02](https://github.com/airone01/ft/commit/d9a8e021a8ca4bf77a08bceefff4798392c0b68a))
* **b:** switch and case statements ([04541b7](https://github.com/airone01/ft/commit/04541b70edda3668e98fa1428a292f80752162a7))
* **b:** while loops ([6e573c3](https://github.com/airone01/ft/commit/6e573c3e60421b812d406e22a66076c29dea4d49))


### Bug Fixes

* **b:** bad substraction order ([845ad6d](https://github.com/airone01/ft/commit/845ad6d66dc4a02d2ca50e8576ea8e26e113613c))
* **b:** clean up compiler optimizations ([5305971](https://github.com/airone01/ft/commit/53059711c90def937e2bedce9802332646c6904a))
* **b:** cleann up some conditions ([dd41d32](https://github.com/airone01/ft/commit/dd41d32b8e6eef451e6767fad4724dbf6c6a020a))
* **b:** highest precedence for unary operators ([efca78b](https://github.com/airone01/ft/commit/efca78b5e1357fc4cc6548e36d909dec38ff5919))
* **b:** lexer 'default' typo ([b356cca](https://github.com/airone01/ft/commit/b356ccacb055750939ba90973283bf987233a6d3))
* **b:** many libb issues ([136ac8a](https://github.com/airone01/ft/commit/136ac8aec24feca2ea82eb19727afb7458fa499a))
* **b:** missing push in math operations ([3fd86c7](https://github.com/airone01/ft/commit/3fd86c70c7285eb70bbd951eebc56cabec3be6ea))
* **b:** opcode typo ([117884e](https://github.com/airone01/ft/commit/117884e348c1a5f828f3a2badede418314a7d2f1))
* **b:** patch last diffs between mine and the school's ([588e91a](https://github.com/airone01/ft/commit/588e91a006dfcd87a4131ed334f51e5a5fe3fcf7))
* **b:** patch some missing stuff ([194f8a1](https://github.com/airone01/ft/commit/194f8a10f5a3f7ed19684c6b55c765b13202faf0))
* **b:** rename tokens ([8484029](https://github.com/airone01/ft/commit/84840293330f46bdfbeff474cd4b806141ba4718))
* **b:** switch syntax error ([4804801](https://github.com/airone01/ft/commit/480480151982b012e3b7732f9790f3f5f24b7bf2))
* **b:** use imul instead of mul ([b849208](https://github.com/airone01/ft/commit/b849208c851b2579c2a72ba4144c219c6cef060e))


### Miscellaneous Chores

* mark beaking changes ([8048a5a](https://github.com/airone01/ft/commit/8048a5a1de58793f73a3202274ae129e9f90e93e))
