
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
('1000', 'Command: .spectate'),
('1001', 'Command: .spectate player'),
('1002', 'Command: .spectate view'),
('1003', 'Command: .spectate reset'),
('1004', 'Command: .spectate leave');

INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES
('195', '1000'),
('195', '1001'),
('195', '1002'),
('195', '1003'),
('195', '1004');
