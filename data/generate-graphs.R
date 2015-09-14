
library("igraph")

vertices <- c(200, 500, 1000, 5000)
densities <- c(0.1, 0.4, 0.5, 0.6, 0.9, 1)

comb <- expand.grid(densities, vertices)
colnames(comb) <- c("p", "n")

info <- data.frame()

for (i in 1:nrow(comb)) {
  n <- comb[i, ]$n
  p <- comb[i, ]$p
  g <- erdos.renyi.game(n, p)
  adj <- get.adjacency(g, sparse = FALSE)
  d <- graph.density(g)
  fname <- paste0("er,", n, ",", p, ".adj")
  info <- rbind(info,
                data.frame(fname, n, p, d))
  cat(fname, "\n")
  print(info)
  write(adj, file = fname, ncolumns = ncol(adj), sep = "")
}

write.table(info, file = "list.txt", sep = " ",
            row.names = FALSE, col.names = FALSE)
