import System.Environment

countLines :: String -> IO Int
countLines file = do
  contents <- readFile file
  return (length $ lines contents)

countWords :: String -> IO Int
countWords file = do
    contents <- readFile file
    return (length $ words contents)
  
main :: IO ()
main = do
  nome_arquivo <- getArgs
  case length nome_arquivo of
    0 -> putStrLn "ERRO : Arquivo informado não encontrado."
    _ -> let file = head nome_arquivo in do
            linhas <- countLines file
            palavras <- countWords file
            putStr $ "Linhas: " ++ show linhas ++ ", palavras: " ++ show palavras ++ "\n"