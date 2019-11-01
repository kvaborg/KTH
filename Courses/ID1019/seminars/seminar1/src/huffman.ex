defmodule Huffman do

  def sample do
    'the quick brown fox jumps over the lazy dog
    this is a sample text that we will use when we build
    up a table we will only handle lower case letters and
    no punctuation symbols the frequency will of course not
    represent english but it is probably not that far off'
  end

  def text() do
    'this is something that we should encode'
  end

  def test do
    sample = read(kallocain.txt, 3200) 
    tree = tree(sample)
    encode = encode_table(tree)
    decode = decode(tree)
    text = text()
    seq = encode(text, encode)
    decode(seq, decode)
  end

  def tree(sample) do
    freq = freq(sample)
    huffman(freq)
  end

  def huffman(freq) do
    sorted = Map.to_list(freq) |> List.keysort(1)
    huffman_tree(sorted) 
  end

  def huffman_tree([{tree, _}]) do tree end
  def huffman_tree([{x, xf}, {y, yf} | rest]) do 
    huffman_tree(insert({{x, y}, xf + yf}, rest))
  end

  def insert({x, xf}, []) do [{x, xf}] end
  def insert({x, xf}, [{y, yf} | rest]) when xf < yf do
    [{x, xf}, {y, yf} | rest]
  end
  def insert({x, xf}, [{y, yf} | rest]) do
    [{y, yf} | insert({x, xf}, rest)]
  end
  
    
  #  Egen men jobbigare implementation
  #
  #  def huffman_tree([{tree, _}]) do tree end
  #  def huffman_tree([head | tail]) do
  #    huffman_tree(insert(head, tail)) 
  #  end
  #
  #  def insert(tree, []) do [tree] end
  #  def insert({x, xf}, [head | tail]) do insert({x, xf}, head, tail) end
  #  def insert({x, xf}, {y, yf}, []) do [{{x, y}, xf + yf}] end
  #  def insert({x, xf}, {y, yf}, [head | tail]) do 
  #    cond do
  #    xf + yf > elem(head, 1) ->
  #      [head | insert({x, xf}, {y, yf}, tail)]
  #    true ->
  #      [{{x, y}, xf + yf} | [head | tail]]
  #    end
  #  end

  def encode_table(tree) do
    char_code(tree, [], []) 
  end
  
  def char_code({l, r}, steps, newlist) do
    left = char_code(l, [0 | steps], newlist)
    char_code(r, [1 | steps], left)
  end

  def char_code(char, steps, list) do 
    [{char, Enum.reverse(steps)} | list]
  end 

  def encode([], _) do [] end
  def encode([char | rest], table) do
    {_, code} = List.keyfind(table, char, 0)
    code ++ encode(rest, table)
  end

  def decode_table(tree) do
    # To implement...
  end

  #  
  def decode([], _) do [] end
  def decode(seq, table) do 
    {char, rest} = decode_char(seq, 1, table)
    [char | decode(rest, table)]
  end

  def decode_char(seq, n, table) do
    {code, rest} = Enum.split(seq, n)
    case List.keyfind(table, code, 1) do
      {char, _} ->
        {char, rest} 
      nil -> decode_char(seq, n + 1, table)
    end
  end
  
  # Calculates the frequency of existing ascii-values (characters)
  def freq(sample) do freq(sample, %{}) end
  def freq([], freq) do freq end
  def freq([char | rest], freq) do
    cond do
      freq[char] === nil ->
        freq(rest, Map.put(freq, char, 1))
      true -> 
        freq(rest, Map.put(freq, char, Map.get(freq, char) + 1))
    end
  end

  def kallocain(file, n) do
    {:ok, file} = File.open(file, [:read])
    binary = IO.read(file, n)
    File.close(file)
    
    case :unicode.characters_to_list(binary, :utf8) do
      {:incomplete, list, _} ->
        list;
      list ->
        list
    end
  end

  # This is the benchmark of the single operations in the
  # Huffman encoding and decoding process.
  def bench(n, coding) do
    {sample, _} = kallocain(n, coding)
    {{text, b}, t1} = time(fn -> kallocain(n, coding) end)
    c = length(text)
    {tree, t2} = time(fn -> tree(sample) end)
    {encode, t3} = time(fn -> encode_table(tree) end)
    s = length(encode)
    {decode, _} = time(fn -> decode_table(tree) end)
    {encoded, t5} = time(fn -> encode(text, encode) end)
    e = div(length(encoded), 8)
    r = Float.round(e / b, 3)
    {_, t6} = time(fn -> decode(encoded, decode) end)

    IO.puts("read in #{t1} ms")
    IO.puts("text of #{c} characters")
    IO.puts("tree built in #{t2} ms")
    IO.puts("table of size #{s} in #{t3} ms")
    IO.puts("encoded in #{t5} ms")
    IO.puts("decoded in #{t6} ms")
    IO.puts("source #{b} bytes, encoded #{e} bytes, compression    #{r}")
  end

  # Measure the execution time of a function.
  def time(func) do
    initial = Time.utc_now()
    result = func.()
    final = Time.utc_now()
    {result, Time.diff(final, initial, :microsecond) / 1000}
  end
end

