defmodule Env do
 
  # Initiates new empty environment
  def new() do [] end 

  # Returns test environment
  def test() do 
    [a: 1, b: 2, c: 3, d: 4, e: 5]
  end

  # Adds new variable binding (key-val pair) to environment
  def add(id, str, []) do [{id, str}] end
  def add(id, str, [{id, _} | t]) do [{id, str} | t] end
  def add(id, str, [h | t]) do 
    [h | add(id, str, t)]
  end 

  # Finds the value of key id in list env
  def lookup(_, []) do nil end
  def lookup(id, [{id, str} | _]) do {id, str} end
  def lookup(id, [_ | t]) do lookup(id, t) end 


  # Removes list of keys from environment
  def remove([], env) do env end  
  def remove([h | t], env) do
    remove(t, remove_var(h, env))
  end

  def remove_var(_, []) do [] end
  def remove_var(id, [{id, _} | t]) do t end
  def remove_var(id, [h | t]) do 
    [h | remove_var(id, t)]
  end 

end
