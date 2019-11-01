defmodule Eager do

  @type atm :: {:atm, atom()}
  @type variable :: {:var, any()}
  @type cons :: {:cons, variable, atm}
  @type ignore :: {:ignore}

  
  def eval_expr({:atm, id}, []) do {:ok, id} end
  def eval_expr({:var, id}, env) do 
    case Env.lookup(id, env) do
      nil ->
        :error 
      {_, str} ->
        {:ok, str} 
    end
  end
  def eval_expr({:cons, expr1, expr2}, env) do
    case eval_expr(expr1, env) do
      :error ->
        :error 
      {:ok, str} ->
        case eval_expr(expr2, env) do
          :error ->
            :error 
          {:ok, ts} ->
            {str, ts} #[str | ts] för bättre utskrift
        end
    end
  end

  def eval_match(:ignore, _, env) do {:ok, env} end
  def eval_match({:atm, id}, id, []) do {:ok, []} end
  def eval_match({:atm, id}, _, []) do :fail end
  def eval_match({:var, id}, str, env) do
    case Env.lookup(id, env) do
      nil ->
        {:ok, Env.add(id, str, env)}
      {_, ^str} ->
        {:ok, env}
      {_, _} ->
        {:ok, Env.add(id, str, env)}
        # :fail (?)
    end
  end
  def eval_match({:cons, hp, tp}, {hstr, tstr}, env) do
    case eval_match(hp, hstr, env) do
      :fail ->
        :fail 
      {:ok, env} ->
        eval_match(tp, tstr, env)
    end
  end
  def eval_match(_, _, _) do :fail end

end
