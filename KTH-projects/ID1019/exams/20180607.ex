defmodule Tenta20180607 do

  @type tree :: {:node, tree(), tree(), integer()} | nil

  def test_tree() do
    {:node, {:node, {:node, nil, nil, 3}, {:node, nil, nil, 3}, 2}, {:node, nil, nil, 2}, 1}
  end

  def fairly({:node, nil, nil, depth}) do depth end
  def fairly({:node, left, nil, _}) do fairly(left) end
  def fairly({:node, nil, right, _}) do fairly(right) end
  def fairly({:node, left, right, 1}) do
    ldepth = fairly(left)
    rdepth = fairly(right)
    cond do
      abs(ldepth - rdepth) <= 1 ->
        {:ok, max(ldepth, rdepth)}
      true ->
        :no
    end
  end 
  def fairly({:node, left, right, _}) do 
    max(fairly(left), fairly(right))
  end
  
  def dillinger() do
    spawn(fn() -> nyc() end)
  end

  def nyc() do
    IO.puts("Hey Jim!")
    receive do
      :cork ->
      knife()
    end
  end

  def knife() do
    receive do
      :knife ->
        fork()
    end
  end

  def fork() do
    receive do
      :fork->
        spoon()
    end
  end

  def spoon() do
    receive do
      :spoon->
       bottle() 
    end
  end

  def bottle() do
    receive do
      :bottle->
        nyc() 
    end
  end
end

