// 1. 获取FunctionCaller对象
FunctionCaller *caller = target.GetFunctionCallerForLanguage(
    language, return_type, function_address, arg_value_list, name, error);

// 2. 编译wrapper
caller->CompileFunction(thread_sp, diagnostics);
caller->WriteFunctionWrapper(exe_ctx, diagnostics);

// 3. 写入参数
caller->WriteFunctionArguments(exe_ctx, args_addr, arg_value_list, diagnostics);

// 4. 生成并执行线程计划
auto plan_sp = caller->GetThreadPlanToCallFunction(
    exe_ctx, args_addr, options, diagnostics);
process->RunThreadPlan(exe_ctx, plan_sp, options, diagnostics);

// 5. 获取返回值
caller->FetchFunctionResults(exe_ctx, args_addr, ret_value);


3. 参考入口
source/Expression/UtilityFunction.cpp 的 UtilityFunction::MakeFunctionCaller
source/Target/Target.cpp 的 Target::GetFunctionCallerForLanguage
include/lldb/Expression/FunctionCaller.h 的 FunctionCaller 类
source/Plugins/ExpressionParser/Clang/ClangFunctionCaller.cpp 的 ClangFunctionCaller
