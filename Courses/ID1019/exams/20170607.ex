defmodule Tenta170607 do

  def transf(x, y, [x|t]) do
    transf(x, y, t)
  end
  def transf(x, y, [h|t]) do
    [h * y | transf(x, y, t)]
  end
  def transf(_, _, []) do [] end

  def sum([h|t]) do
    sum([h|t], 0)
  end
  def sum([], sum) do sum end
  def sum([h|t], sum) do
    sum(t, sum + h)
  end

  #  def reduce([x, y | t]) do
  #    reduce([x, y | t], [])
  #  end
  #  def reduce([], done) do done end
  #  def reduce([x, y | t], acc) do
  #    case x do
  #      y ->
  #        reduce([y|t], acc)
  #      _ ->
  #        reduce([y|t], x ++ acc)
  #    end
  #  end

  def reduce([]) do [] end
  def reduce([x, x | t]) do reduce([x|t]) end
  def reduce([x | t]) do [x | reduce(t)] end

  def encode([]) do [] end
  def encode([h|t]) when h < 100 do 
    [h+23 | encode(t)]
  end
  def encode([32|t]) do
    [32 | encode(t)]
  end
  def encode([h|t]) do
    [h-3 | encode(t)]
  end

  def triss([]) do false end
  def triss([h|t] = l) do 
    case :lists.filter(fn(x) -> x == h end, l) do
      [_, _, _] ->
        true
      _ -> 
        triss(t)
    end
  end

  def msort([]) do [] end
  def msort(list) do 
    {l1, l2} = Enum.split(list, length(list))
    merge(msort(l1), msort(l2))
  end

  def merge([], r) do r end
  def merge(l, []) do l end
  def merge([h1|t1] = l1, [h2|t2] = l2) do
    cond do 
      h1 < h2 ->
        [h1 | merge(t1,l2)]
      true ->
        [h2 | merge(l1,t2)]
    end
  end 

  @type heap :: {:heap, integer(), heap(), heap()} | nil

  def heap_to_list(nil) do [] end
  def heap_to_list({:heap, val, l, r}) do 
    left = heap_to_list(l)
    right = heap_to_list(r)
    [val | merge(left, right)]
  end
  
  @type tree :: {:node, integer(), tree(), tree()} | nil

  def test_tree() do
    {:node, 5, {:node, 3, {:node, 1, nil, nil}, nil}, {:node, 4 ,nil, nil}}
  end

  def mint(tree) do mint(tree, :inf) end

  def mint(nil, min) do min end
  def mint({:node, val, l, r}, min) do
    cond do
      val < min ->
        mint(l, mint(r, val))
        IO.puts("val: #{val}")
      true ->
        mint(l, mint(r, min))
    end
  end
  
  # def mint(nil, _) do :inf end
  # def mint({:node, val, l, r}, min_elem) do
  #   {_, vl, _, _} = min(l, min_elem)
  #   {_, rl, _, _} = min(r, min_elem)

  #   cond do
  #     vl < rl ->
  #      vl 
  #     true ->
  #      rl 
  #   end
  # end
  # def mint({:node, val, nil, nil}, min_elem) do
  #   cond do
  #     val < min_elem ->
  #       [val]
  #     true ->
  #       [min_elem]
  #   end
  # end

end
