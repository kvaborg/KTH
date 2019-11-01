defmodule Tenta2019 do
  
  @type tree() :: nil | {:node, any(), tree(), tree()}

  def test_seq() do
    [{:a, 2}, {:c, 1}, {:b, 3}, {:a, 1}]
  end
  
  def test_tree1() do
    {:node, 1, {:node, 2, {:node, 3, nil, nil}, nil}, {:node,4, nil, nil}}
  end

  def decode([]) do [] end
  def decode([{ch, n} | t]) when n>1 do
    [ch | decode([{ch, n-1}|t])]
  end
  def decode([{ch, 1}|t]) do
    [ch | decode(t)]
  end 

  def decode2([]) do [] end
  def decode2([{_, 1} | t]) do decode2(t) end
  def decode2([{char, num} | t]) do
    [char | decode([{char, num - 1} | t])]
  end

  def zip([],[]) do [] end
  def zip([h1|t1], [h2|t2]) do
    [{h1, h2} | zip(t1,t2)]
  end

  def balance(nil) do {0,0} end
  def balance({:node, int, l, r}) do
    {dl, il} = balance(l)
    {dr, ir} = balance(r)
    depth = max(dl, dr) + 1
    IO.inspect(max(il,ir), label: 'max')
    imb = max(max(il, ir), abs(dl - dr))
    IO.inspect({depth, imb}, label: int)
  end

  def eval({:add, a, b}) do eval(a) + eval(b) end
  def eval({:mul, a, b}) do eval(a) * eval(b) end
  def eval({:neg, a}) do eval(-a) end
  def eval(a) do a end

  def gray(0) do [[]] end
  def gray(n) do
    g = gray(n-1)
    g_rev = Enum.reverse(g)
    update(g, 0) ++ update(g_rev, 1)
  end

  def update([], _) do [] end
  def update([h|t], b) do
    [[b|h] | update(t, b)]
  end
  
  def add({:queue, front, back}, elem) do
    {:queue, front, [elem|back]}
  end

  def remove({:queue, [elem|rest], back}) do
    {:ok, elem, {:queue, rest, back}}
  end

  def remove({:queue, [], back}) do
    case Enum.reverse(back) do
      [] ->
        :fail
      [elem|rest] ->
        {:ok, elem, {:queue, rest, []}}
    end
  end

end 
