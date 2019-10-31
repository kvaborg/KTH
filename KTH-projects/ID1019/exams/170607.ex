defmodule Ten170607 do

  def transf(_, _, []) do [] end
  def transf(x, y, [x|t]) do
    transf(x,y,t)
  end
  def transf(x,y,[h|t]) do
    [h*y | transf(x,y,t)]
  end

  def sum(list) do sum(list, 0) end
  def sum([], acc) do acc end
  def sum([h|t], acc) do sum(t, acc + h) end

  def test_tree() do
    {:node, 5, {:node, 3, nil, {:node, 1, nil, nil}}, {:node, 2, nil, nil}}
  end

  def minn(tree) do minn(tree, :inf) end
  def minn(nil, m) do m end
  def minn({:node, val, l, r}, m) do
    if val < m do
      IO.puts('if')
      IO.inspect(l)
      IO.inspect(r)
      minn(l, minn(r, val))
    else
      IO.puts('else')
      IO.inspect(l)
      IO.inspect(r)
      minn(l, minn(r, m))
    end
  end
end
